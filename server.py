import json 
import serial 
import argparse
import websockets
import asyncio
import logging

# Global variables for each robot
class RobotConnection:
    def __init__(self, port, baudrate):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.connected = False

# Create robot connections
left_robot = RobotConnection("COM6", 115200)
right_robot = RobotConnection("COM4", 115200)

# Global configuration
position_scale = 1000.0
position_offset = {"x": 0.0, "y": 0.0, "z": 0.0} #FIX Z_OFFSET LATER

# Robot constraints
X_MIN = -330
X_MAX = 330
Y_MIN = -330
Y_MAX = 330
Z_MIN = 0
Z_MAX = 330


def map_to_robot_range(value, axis):
    if axis == "x":
        clamped = max(X_MIN, min(value, X_MAX))
    elif axis == "y":
        clamped = max(Y_MIN, min(value, Y_MAX))
    elif axis == "z":
        clamped = max(Z_MIN, min(value, Z_MAX))
    return int(clamped)

def transform_coordinates(hand_x, hand_y, hand_z):    
    robot_x = (400 - hand_y) * position_scale
    robot_y = (400 - hand_x) * position_scale
    robot_z = (hand_z + position_offset["z"]) * position_scale
    
    robot_x = map_to_robot_range(robot_x, "x")
    robot_y = map_to_robot_range(robot_y, "y")
    robot_z = map_to_robot_range(robot_z, "z")

    if robot_z < 0:
        robot_z = 0
    
    return robot_x, robot_y, robot_z

def connect_robot(robot):

    if not robot.connected:
        try:
            if robot.serial:
                robot.serial.close()
            
            #establishing a connection to the robot
            robot.serial = serial.Serial(robot.port, baudrate=robot.baudrate, timeout=0.1, dsrdtr=None)
            robot.serial.setRTS(False)
            robot.serial.setDTR(False)
            robot.connected = True
            print(f"Connected to {robot.port} at {robot.baudrate} baud")
        except Exception as e:
            logging.error(f"Failed to connect to {robot.port}: {str(e)}")
            robot.connected = False
            if robot.serial:
                robot.serial.close()

def send_command_to_robot(robot, command):
    if robot.connected and robot.serial:
        try:
            cmd_json = json.dumps(command)
            robot.serial.write(cmd_json.encode('utf-8'))
            robot.serial.write(b'\n')
            print(f"Sent to robot on {robot.port}: {cmd_json}")
        except Exception as e:
            print(f"Error sending command to {robot.port}: {str(e)}")
            robot.connected = False

async def handle_connections(websocket):
    logging.warning("Connected to Client")

    try:
        async for msg in websocket:
            print(f"RECEIVED: {msg}")
            
            try:
                # Parse the JSON message from Unity
                data = json.loads(msg)
                
                # Process hand position data
                if 'T' in data and data['T'] == 1041:  # Command type 1041 is "CMD_XYZT_DIRECT_CTRL"
                    # Get hand position values
                    hand_x = float(data.get('x', 0))
                    hand_y = float(data.get('y', 0))
                    hand_z = float(data.get('z', 0))
                    hand_t = float(data.get('t', 0))
                    hand_g = float(data.get('g', 0))
                    hand_type = data.get('handType', None)

                    # Select the appropriate robot
                    robot = left_robot if hand_type == "Left" else right_robot
                    
                    # Transform coordinates
                    robot_x, robot_y, robot_z = transform_coordinates(hand_x, hand_y, hand_z)
                    
                    print(f"Hand coordinates - X: {hand_x}, Y: {hand_y}, Z: {hand_z}")
                    print(f"Mapped robot coordinates - X: {robot_x}, Y: {robot_y}, Z: {robot_z}, T: {hand_t}")
                    
                    # Create robot command with integer coordinates
                    robot_command = {
                        "T": 1041,
                        "x": robot_x,
                        "y": robot_y,
                        "z": robot_z,
                        "t": hand_t,
                        "r": 0,
                        "g": hand_g
                    }
                    
                    # Ensure connection and send command
                    connect_robot(robot)
                    send_command_to_robot(robot, robot_command)
                
                elif 'port' in data or 'baudrate' in data or 'position_scale' in data or 'position_offset' in data:
                    global position_scale, position_offset
                    
                    if 'position_scale' in data:
                        position_scale = float(data['position_scale'])
                    if 'position_offset' in data:
                        position_offset = data['position_offset']
                        
                    print(f"Updated settings - Position scale: {position_scale}, Offset: {position_offset}")
                    
            except json.JSONDecodeError:
                logging.error("Received invalid JSON message")
            except Exception as e:
                logging.error(f"Error processing message: {str(e)}")
            
    except websockets.ConnectionClosed as e:
        logging.error("Connection was closed")
    except Exception as e:
        logging.error(f"Error occurred: {str(e)}")

async def main():
    parser = argparse.ArgumentParser(description="Robot Connection parameters")
    parser.add_argument("-w", "--websocket_port", type=int, default=8766)

    args = parser.parse_args()


    # Start the websocket server
    server = await websockets.serve(handle_connections, "localhost", args.websocket_port)
    print(f"WebSocket server started on ws://localhost:{args.websocket_port}")
    print(f"Position scale: {position_scale}")

    
    await server.wait_closed()

if __name__ == "__main__":
    asyncio.run(main())
