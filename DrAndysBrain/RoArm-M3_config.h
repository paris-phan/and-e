// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define RoArmM3_Servo_RXD 18
#define RoArmM3_Servo_TXD 19

// 2: flow feedback.
// 1: [default]print debug info in serial.
// 0: don't print debug info in serial.
byte InfoPrint = 2;

// devices info:
// espNowMode: 0 - none
//             1 - flow-leader(group): sending cmds
//             2 - flow-leader(single): sending cmds to a single follower
//             3 - [default]follower: recv cmds
byte espNowMode = 3;

// set the broadcast ctrl mode.
// broadcast mac address: FF:FF:FF:FF:FF:FF.
// true  - [default]it can be controled by broadcast mac address.
// false - it won't be controled by broadcast mac address.
bool ctrlByBroadcast = true;

// you can define some whitelist mac addresses here.
uint8_t mac_whitelist_broadcast[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// the mac that esp-now cmd received from
uint8_t mac_received_from[6];

// Multifunction End-Effector Switching System.
// 0 - end servo as grab.
// 1 - end servo as a joint moving in vertical plane.
byte EEMode = 1;

// esp-now run json block cmd
// false: can not run esp-now block cmd
// true:  it can process esp-now block cmd but there'll be a delay
bool espNowRunBlockCmd = true;

// run new json cmd
bool runNewJsonCmd = false;


#define BASE_JOINT     1
#define SHOULDER_JOINT 2
#define ELBOW_JOINT    3
#define WRIST_JOINT    4
#define ROLL_JOINT     5

#define EOAT_JOINT     6


// define servoID
//   |---[14]---|
//   ||  |  |  ||
//   ||        ||
//   ||  |  |  ||
//   ||        ||
//   ||  |  |  ||
//   || -[15]- ||
//   ||        ||
//   ||[13][12]||
//     |  __  |
//       [11]
//
// --[17]-O-[16]-O-[15]
// ------              
                    
#define BASE_SERVO_ID    11
#define SHOULDER_DRIVING_SERVO_ID 12
#define SHOULDER_DRIVEN_SERVO_ID  13
#define ELBOW_SERVO_ID   14
#define WRIST_SERVO_ID   15
#define ROLL_SERVO_ID    16
#define GRIPPER_SERVO_ID 1

#define ARM_SERVO_MIDDLE_POS  2047
#define ARM_SERVO_MIDDLE_ANGLE 180
#define ARM_SERVO_POS_RANGE   4096
#define ARM_SERVO_ANGLE_RANGE  360
#define ARM_SERVO_INIT_SPEED   600
#define ARM_SERVO_INIT_ACC      20

#define ARM_L1_LENGTH_MM    126.06
#define ARM_L2_LENGTH_MM_A  236.82
#define ARM_L2_LENGTH_MM_B	30.00 
#define ARM_L3_LENGTH_MM_A_0	215.99 //orig 144.49 m3, 280.15 m2
#define ARM_L3_LENGTH_MM_B_0	0

// 	  TYPE:0
//    -------L3A-----------O==L2B===\
//    |                    ^       ||
//   L3B                   |       ||
//    |              ELBOW_JOINT   ||
//                                L2A
//                                 ||
//                                 ||
//                                 ||
//               SHOULDER_JOINT -> OO
//                                [||]
//                                 L1
//                                [||]
//                   BASE_JOINT -> X
double l1  = ARM_L1_LENGTH_MM;
double l2A = ARM_L2_LENGTH_MM_A;
double l2B = ARM_L2_LENGTH_MM_B;
double l2  = sqrt(l2A * l2A + l2B * l2B);
double t2rad = atan2(l2B, l2A);
double l3A = ARM_L3_LENGTH_MM_A_0;
double l3B = ARM_L3_LENGTH_MM_B_0;
double l3  = sqrt(l3A * l3A + l3B * l3B);
double t3rad = atan2(l3B, l3A);


#define ARM_L3_LENGTH_MM_A_1	215.99 //orig 144.49 m3, 215.9 m2
#define ARM_L3_LENGTH_MM_B_1	0

// edge
// CENTER OF CLAW = 136.84
// END OF CLAW = 190.29
double ARM_L4_LENGTH_MM_A =	136.84; //orig 171.67 m3, 67.85 m2

// D-3.2
// double ARM_L4_LENGTH_MM_A =	64.16;

// D-4.2
// double ARM_L4_LENGTH_MM_A =	59.07;

// D-10.2
// double ARM_L4_LENGTH_MM_A =	51.07;

#define ARM_L4_LENGTH_MM_B  0 //orig 13.69 m3

//    TYPE:1
//                   -------L3A-----------O==L2B===
//                   |                    ^       ||
//                  L3B                   |       ||
//                   |              ELBOW_JOINT   ||
//          ---L4A---O                           L2A
//          |                                     ||
//     |   L4B                                    ||
//   /      |                                     ||
// 180°X-EA-X                   SHOULDER_JOINT -> OO
//   \ |                                         [||]
//    EB                                          L1
//     |                                         [||]
//    --------                      BASE_JOINT -> XX

// 		\  T:210°
// 		 \
//  	  EB
//   	   \
// 		-----------

double EoAT_A = 0;
double EoAT_B = 0;
double l4A = ARM_L4_LENGTH_MM_A;
double l4B = ARM_L4_LENGTH_MM_B;
double lEA = EoAT_A + ARM_L4_LENGTH_MM_A;
double lEB = EoAT_B + ARM_L4_LENGTH_MM_B;
double lE  = sqrt(lEA * lEA + lEB * lEB);
double tErad = atan2(lEB, lEA);


double initX = l2B + l3A + ARM_L4_LENGTH_MM_A; //
double initY = 0;
double initZ = l2A - ARM_L4_LENGTH_MM_B;
double initT = 0;
double initR = 0;
double initG = 3.14 / 3;


double goalX = initX;
double goalY = initY;
double goalZ = initZ;
double goalT = initT;
double goalR = initR;
double goalG = initG;


double lastX = goalX;
double lastY = goalY;
double lastZ = goalZ;
double lastT = goalT;
double lastR = goalR;
double lastG = goalG;


double base_r;

double delta_x;
double delta_y;

double beta_x;
double beta_y;



double radB;
double radS;
double radE;

double radT;
double radR;

double radG;



#define MAX_SERVO_ID 32 // MAX:253

// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 18
#define S_TXD 19

double BASE_JOINT_RAD = 0;
double SHOULDER_JOINT_RAD = 0;
double ELBOW_JOINT_RAD = M_PI/2;
double WRIST_JOINT_RAD = 0;
double ROLL_JOINT_RAD = 0;
double EOAT_JOINT_RAD = M_PI;
double EOAT_JOINT_RAD_BUFFER;

double BASE_JOINT_ANG  = 0;
double SHOULDER_JOINT_ANG = 0;
double ELBOW_JOINT_ANG = 90.0;
double WRIST_JOINT_ANG = 0;
double ROLL_JOINT_ANG = 0;
double EOAT_JOINT_ANG  = 180.0;

// true: torqueLock ON, servo produces torque.
// false: torqueLock OFF, servo release torque.
bool RoArmM3_torqueLock = true;
bool RoArmM3_emergencyStopFlag = false;
bool newCmdReceived = false;

bool nanIK;

bool RoArmM3_initCheckSucceed  = false;
// bool RoArmM3_initCheckSucceed   = true;

// // // args for syncWritePos.
u8  servoID[7] = {11, 12, 13, 14, 15, 16, 1};
s16 goalPos[7] = {2047, 2047, 2047, 2047, 2047, 2047, 2047};
u16 moveSpd[7] = {0, 0, 0, 0, 0, 0, 0};
u8  moveAcc[7] = {ARM_SERVO_INIT_ACC,
			      ARM_SERVO_INIT_ACC,
			      ARM_SERVO_INIT_ACC,
			      ARM_SERVO_INIT_ACC,
			      ARM_SERVO_INIT_ACC,
			      ARM_SERVO_INIT_ACC,
			  	  ARM_SERVO_INIT_ACC};


double ARM_BASE_LIMIT_MIN_RAD     = -M_PI/2;
double ARM_BASE_LIMIT_MAX_RAD     =  M_PI/2;

double ARM_SHOULDER_LIMIT_MIN_RAD = -M_PI/2;
double ARM_SHOULDER_LIMIT_MAX_RAD =  M_PI/2;

double ARM_ELBOW_LIMIT_MIN_RAD    = -M_PI/4; // reduced from /2
double ARM_ELBOW_LIMIT_MAX_RAD    =  M_PI/4; 

double ARM_GRIPPER_LIMIT_MIN_RAD  = -M_PI/2;
double ARM_GRIPPER_LIMIT_MAX_RAD  =  M_PI/2;


// --- --- --- Pneumatic Components && Lights --- --- ---

const uint16_t ANALOG_WRITE_BITS = 8;
const uint16_t MAX_PWM = pow(2, ANALOG_WRITE_BITS)-1;
const uint16_t MIN_PWM = MAX_PWM/4;

#define PWMA 25         // Motor A PWM control  
#define AIN2 17         // Motor A input 2     
#define AIN1 21         // Motor A input 1     
#define BIN1 22         // Motor B input 1       
#define BIN2 23         // Motor B input 2       
#define PWMB 26         // Motor B PWM control  

#define AENCA 35        // Encoder A input      
#define AENCB 34

#define BENCB 16        // Encoder B input     
#define BENCA 27

int freq = 100000;
int channel_A = 5;
int channel_B = 6;


// --- --- --- Bus Servo Settings --- --- ---

#define ST_PID_P_ADDR 21
#define ST_PID_D_ADDR 22
#define ST_PID_I_ADDR 23

#define ST_PID_ROARM_P   16
#define ST_PID_DEFAULT_P 32

#define ST_TORQUE_MAX 1000
#define ST_TORQUE_MIN 50


// --- --- --- i2c Settings --- --- ---

#define S_SCL   33
#define S_SDA   32


//  --- --- --- web / constant moving --- --- ---

#define MOVE_STOP 0
#define MOVE_INCREASE 1
#define MOVE_DECREASE 2

#define CONST_ANGLE 0
#define CONST_XYZT  1

float const_spd;
byte  const_mode;

byte const_cmd_base_x;
byte const_cmd_shoulder_y;
byte const_cmd_elbow_z;
byte const_cmd_wrist_t;
byte const_cmd_roll_r;
byte const_cmd_eoat_g;

float const_goal_base = BASE_JOINT_ANG;
float const_goal_shoulder = SHOULDER_JOINT_ANG;
float const_goal_elbow = ELBOW_JOINT_ANG;
float const_goal_wrist = WRIST_JOINT_ANG;
float const_goal_roll = ROLL_JOINT_ANG;
float const_goal_eoat = EOAT_JOINT_ANG;

unsigned long prev_time = 0;

String jsonFeedbackWeb = "";