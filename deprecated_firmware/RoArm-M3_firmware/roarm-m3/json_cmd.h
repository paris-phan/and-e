// emergency stop.
// {"T":0}
#define CMD_EMERGENCY_STOP 0

// reset emergency flag.
// {"T":999}
#define CMD_RESET_EMERGENCY 999


// ---===< Arm ctrl. >===---

// it moves to goal position directly.
// without interpolation.
// {"T":100}
#define CMD_MOVE_INIT 100

// {"T":101,"joint":0,"rad":0,"spd":0,"acc":10}
// joint: 1-BASE_JOINT + ->left
//        2-SHOULDER_JOINT + ->down
//        3-ELBOW_JOINT + ->down
//        4-EOAT_JOINT + ->grab/down
// spd: steps/s
// acc: steps/s^2
#define CMD_SINGLE_JOINT_CTRL 101

// M3-C
// {"T":102,"base":0,"shoulder":0,"elbow":1.57,"wrist":0,"hand":1.57,"spd":0,"acc":10}
// input the angle in rad(180°=3.1415926).
#define CMD_JOINTS_RAD_CTRL 102

// {"T":103,"axis":2,"pos":0,"spd":0.25}
// axis: 1-x: 235.11
//       2-y: 0
//       3-z: 234.79
//       4-t: 1.57
#define CMD_SINGLE_AXIS_CTRL 103

// M3-C
// // // // // // // // // // // // // // // // // // // // //
// {"T":104,"x":235,"y":0,"z":234,"t":0,"r":0,"g":3.14,"spd":0.25}
#define CMD_XYZT_GOAL_CTRL 104                              //
// // // // // // // // // // // // // // // // // // // // //

// M3-C
// {"T":1041,"x":235,"y":0,"z":234,"t":0,"r":0,"g":3.14}
#define CMD_XYZT_DIRECT_CTRL 1041


// {"T":105}
// x: real x position.
// y: real y position.
// z: real z position.
// t: real grab/hand angle in rad.
// torB: base joint torque.
// torS: shoulder joint torque.
// torE: elbow joint torque.
#define CMD_SERVO_RAD_FEEDBACK 105

// release:
// {"T":106,"cmd":1.57,"spd":0,"acc":0}
// grab:
// {"T":106,"cmd":3.14,"spd":0,"acc":0}
// hand joint ctrl using angle in radius.
// {"T":106,"cmd":4.0,"spd":0,"acc":0}
#define CMD_EOAT_HAND_CTRL 106

// {"T":107,"tor":200}
#define CMD_EOAT_GRAB_TORQUE 107

// {"T":108,"joint":3,"p":16,"i":0}
// change the P&I of a joint.
// BASE_JOINT     - 1
// SHOULDER_JOINT - 2
// ELBOW_JOINT    - 3
// EOAT_JOINT     - 4
// default p:32[servo] 16[RoArm-M2]
//         i: 0[servo]  8[RoArm-M2 PID MODE ON]
//         d: not used by default
#define CMD_SET_JOINT_PID 108

// {"T":109}
// reset the PID.
#define CMD_RESET_PID 109

// set a new x-axis.
// {"T":110,"xAxisAngle":0}
#define CMD_SET_NEW_X 110

// set delay time
// {"T":111,"cmd":3000}
#define CMD_DELAY_MILLIS 111

// dynamic external force adaptation.   M3-C
// mode: 0 - stop: reset every limit torque to 1000.
//       1 - start: set the joint limit torque. 
// b, s, e, h = bassJoint, shoulderJoint, elbowJoint, handJoint
// example:
// starts. input the limit torque of every joint.
// {"T":112,"mode":1,"b":60,"s":110,"e":50,"t":50,"r":50,"h":50}
// stop
// {"T":112,"mode":0,"b":1000,"s":1000,"e":1000,"t":1000,"r":1000,"h":1000}  
#define CMD_DYNAMIC_ADAPTATION 112

// switch-12V ctrl.
// pwm: -255 ~ 0(off) ~ +255
// {"T":113,"pwm_a":-255,"pwm_b":-255}
#define CMD_SWITCH_CTRL 113

// light ctrl.
// led: 0(off) - 255(max)
// {"T":114,"led":255}
#define CMD_LIGHT_CTRL 114

// switch off.
// {"T":115}
#define CMD_SWITCH_OFF 115

// ctrl a single joint abs angle in deg.
// joint: 1-BASE_JOINT + ->left
//        2-SHOULDER_JOINT + ->down
//        3-ELBOW_JOINT + ->down
//        4-EOAT_JOINT + ->grab/down
// spd: speed, angle/s^2
// acc: speed, angle/s^2 (max: 22.5)
// {"T":121,"joint":1,"angle":0,"spd":10,"acc":10}
#define CMD_SINGLE_JOINT_ANGLE 121

// M3-C
// ctrl all joints
// b - BASE
// s - SHOULDER
// e - ELBOW
// h - HAND
// spd - angle/s
// acc - angle/s^2 (max: 22.5)
// {"T":122,"b":0,"s":0,"e":90,"t":0,"r":0,"h":180,"spd":10,"acc":10}
#define CMD_JOINTS_ANGLE_CTRL  122

// constant ctrl
// m: 0 - angle
//    1 - xyzt
// cmd: 0 - stop
// 		1 - increase
// 		2 - decrease
// {"T":123,"m":0,"axis":0,"cmd":0,"spd":3}
#define CMD_CONSTANT_CTRL  123



// === === === MISSION CTRL & FILE CTRL === === ===

// scan files in flash.
// {"T":200}
#define CMD_SCAN_FILES 200

// create a new file and input the content.
// {"T":201,"name":"file.txt","content":"inputContentHere."}
#define CMD_CREATE_FILE 201

// get a file content.
// {"T":202,"name":"file.txt"}
#define CMD_READ_FILE 202

// remove a file in flash.
// {"T":203,"name":"file.txt"}
#define CMD_DELETE_FILE 203

// add a line at the end of a file.
// {"T":204,"name":"file.txt","content":"inputContentHere."}
#define CMD_APPEND_LINE 204

// insert a new line as lineNum.
// {"T":205,"name":"file.txt","lineNum":3,"content":"content"}
#define CMD_INSERT_LINE 205

// change a single line in the file.
// {"T":206,"name":"file.txt","lineNum":3,"content":"Content"}
#define CMD_REPLACE_LINE 206

// read a single line from file.
// {"T":207,"name":"file.txt","lineNum":3}
#define CMD_READ_LINE 207

// delete a single line from file.
// {"T":208,"name":"file.txt","lineNum":3}
#define CMD_DELETE_LINE 208


// torque-lock ctrl.
// off: {"T":210,"cmd":0}
//  on: {"T":210,"cmd":1}
#define CMD_TORQUE_CTRL 210



// === === === mission & steps edit. === === ===

// create a mission in flash: 
// {"T":220,"name":"mission_a","intro":"test mission created in flash."}
#define CMD_CREATE_MISSION 220

// input the mission name and get the total content.
// {"T":221,"name":"mission_a"}
#define CMD_MISSION_CONTENT  221



// M3-C
// append a new step at the end of the mission, using the step input.
// {"T":222,"name":"mission_a","step":"{\"T\":104,\"x\":235,\"y\":0,\"z\":234,\"t\":3.14,\"r\":0,\"g\":0,\"spd\":0.25}"}
#define CMD_APPEND_STEP_JSON 222

// append a new step at the end of the mission, using the feedback.
// {"T":223,"name":"mission_a","spd":0.25}
#define CMD_APPEND_STEP_FB 223

// append a new delay(ms) at the end of the mission.
// {"T":224,"name":"mission_a","delay":3000}
#define CMD_APPEND_DELAY 224



// insert a new step as the stepNum
// using the json string input.
// {"T":225,"name":"mission_a","stepNum":3,"step":"{\"T\":104,\"x\":235,\"y\":0,\"z\":234,\"t\":3.14,\"spd\":0.25}"}
// {"T":225,"name":"mission_a","stepNum":3,"step":"{\"T\":114,\"led\":255}"}
#define CMD_INSERT_STEP_JSON 225

// insert a new step as the stepNum
// using the feedback.
// {"T":226,"name":"mission_a","stepNum":3,"spd":0.25}
#define CMD_INSERT_STEP_FB 226

// insert a new delay(ms) at the stepNum.
// {"T":227,"stepNum":3,"delay":3000}
#define CMD_INSERT_DELAY 227



// replace the cmd at stepNum
// using json cmd input.
// {"T":228,"name":"mission_a","stepNum":3,"step":"{\"T\":114,\"led\":255}"}
#define CMD_REPLACE_STEP_JSON 228

// replace the cmd at stepNum
// using feedback.
// {"T":229,"name":"mission_a","stepNum":3,"spd":0.25}
#define CMD_REPLACE_STEP_FB 229

// replace the cmd at stepNum with delay cmd.
// {"T":230,"name":"mission_a","stepNum":3,"delay":3000}
#define CMD_REPLACE_DELAY 230


// delete a step
// {"T":231,"name":"mission_a","stepNum":3}
#define CMD_DELETE_STEP 231


// input the mission name and a stepNum, it will move to the step.
// {"T":241,"name":"mission_a","stepNum":3}
#define CMD_MOVE_TO_STEP 241

// input the mission name and repeatTimes to play a mission.
// if repeatTimes = -1, it will loop forever.
// {"T":242,"name":"mission_a","times":3}
#define CMD_MISSION_PLAY 242



// === === === ESP-NOW settings. === === ===

// note: wifi must be running under STA(AP+STA) mode.
// it will be controled by broadcast mac address.
// {"T":300,"mode":1}
// it won't be controled by broadcast mac address, and add one mac to whitelist.
// if there is no leader you can just fill 00:00:00:00:00:00 in it.
// {"T":300,"mode":0,"mac":"CC:DB:A7:5B:E4:1C"}
#define CMD_BROADCAST_FOLLOWER 300

// set the mode of esp-now
// espNowMode: 0 - none
//             1 - flow-leader(group): sending cmds
//             2 - flow-leader(single): sending cmds to a single follower
//             3 - [default]follower: recv cmds
// flow-leader - use cmd=0, ctrl servos in real time.
//               leader uses the servos feedback pos to ctrl followers.
// {"T":301,"mode":3}
#define CMD_ESP_NOW_CONFIG    301

// get this dev mac address.
// {"T":302}
#define CMD_GET_MAC_ADDRESS   302

// add a new follower mac address to peer.
// {"T":303,"mac":"FF:FF:FF:FF:FF:FF"}
// {"T":303,"mac":"CC:DB:A7:5B:E4:1C"}
// {"T":303,"mac":"CC:DB:A7:5C:1C:40"}
// {"T":303,"mac":"CC:DB:A7:5C:E5:FC"}
#define CMD_ESP_NOW_ADD_FOLLOWER  303

// remove a follower from peer.
// {"T":304,"mac":"FF:FF:FF:FF:FF:FF"}
// {"T":304,"mac":"CC:DB:A7:5B:E4:1C"}
// {"T":304,"mac":"CC:DB:A7:5C:1C:40"}
// {"T":304,"mac":"CC:DB:A7:5C:E5:FC"}
#define CMD_ESP_NOW_REMOVE_FOLLOWER 304

// M3-C
// send info to more than one peer devs.
// "FF:FF:FF:FF:FF:FF" can't be in the broadcast peer.
// {"T":305,"dev":0,"b":0,"s":0,"e":1.57,"t":0,"r":0,"h":1.57,"cmd":0,"megs":"hello!"}
#define CMD_ESP_NOW_GROUP_CTRL 305

// M3-C
// send info to a single dev, or to every devs by using "FF:FF:FF:FF:FF:FF"
// broadcast ctrl:
// {"T":306,"mac":"FF:FF:FF:FF:FF:FF","dev":0,"b":0,"s":0,"e":1.57,"t":0,"r":0,"h":1.57,"cmd":0,"megs":"hello!"}
// {"T":306,"mac":"FF:FF:FF:FF:FF:FF","dev":0,"b":0,"s":0,"e":0,"t":0,"r":0,"h":0,"cmd":1,"megs":"{\"T\":114,\"led\":255}"}
// single ctrl:
// {"T":306,"mac":"CC:DB:A7:5C:E5:FC","dev":0,"b":0,"s":0,"e":1.57,"t":0,"r":0,"h":1.57,"cmd":0,"megs":"hello!"}
#define CMD_ESP_NOW_SINGLE 306



// === === === wifi settings. === === ===

// config the wifi mode on boot.
// 0 - off
// 1 - ap
// 2 - sta
// 3 - ap+sta
// {"T":401,"cmd":3}
#define CMD_WIFI_ON_BOOT 401

// M3-C
// config ap mode.
// {"T":402,"ssid":"RoArm-M3","password":"12345678"}
#define CMD_SET_AP  402

// config sta mode.
// {"T":403,"ssid":"JSBZY-2.4G","password":"waveshare0755"}
#define CMD_SET_STA 403

// M3-C
// config ap/sta mode.
// {"T":404,"ap_ssid":"RoArm-M3","ap_password":"12345678","sta_ssid":"JSBZY-2.4G","sta_password":"waveshare0755"}
#define CMD_WIFI_APSTA   404

// get wifi info.
// {"T":405}
#define CMD_WIFI_INFO    405

// create a wifiConfig.json file
// from the args already be using.
// {"T":406}
#define CMD_WIFI_CONFIG_CREATE_BY_STATUS 406

// M3-C
// create a wifiConfig.json file
// from the args input.
// {"T":407,"mode":3,"ap_ssid":"RoArm-M3","ap_password":"12345678","sta_ssid":"JSBZY-2.4G","sta_password":"waveshare0755"}
#define CMD_WIFI_CONFIG_CREATE_BY_INPUT 407

// disconnect wifi.
// {"T":408}
#define CMD_WIFI_STOP 408



// === === === servo settings. === === ===

// change a servo's ID.
// {"T":501,"raw":1,"new":11}
#define CMD_SET_SERVO_ID 501

// set the current position as the middle position.
// > BASE_SERVO_ID    11
// > SHOULDER_DRIVING_SERVO_ID 12
// > SHOULDER_DRIVEN_SERVO_ID  13
// > ELBOW_SERVO_ID   14
// > GRIPPER_SERVO_ID 15
// {"T":502,"id":11}
#define CMD_SET_MIDDLE   502

// set the P/PID of a single servo.
// {"T":503,"id":14,"p":16}
#define CMD_SET_SERVO_PID   503



// === === === esp32 settings. === === ===

// esp-32 ctrl.
// reboot device.
// {"T":600}
#define CMD_REBOOT 600

// get the size of free flash space
// {"T":601}
#define CMD_FREE_FLASH_SPACE 601

// boot mission info.
// {"T":602}
#define CMD_BOOT_MISSION_INFO 602

// reset boot mission.
// {"T":603}
#define CMD_RESET_BOOT_MISSION 603

// if there is something wrong with wifi funcs, clear the nvs.
// {"T":604}
#define CMD_NVS_CLEAR 604

// 2: flow feedback.
// 1: [default]print debug info in serial.
// 0: don't print debug info in serial.
// {"T":605,"cmd":1}
#define CMD_INFO_PRINT 605