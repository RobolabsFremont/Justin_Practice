/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       robol                                                     */
/*    Created:      9/9/2026, 7:12:10 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
motor LeftDrive;
motor RightDrive;
motor ArmMotor;
motor ClawMotor;
controller Controller1 = controller(primary);

motor LeftDrive1 = motor(PORT1, gearSetting::ratio6_1, false);
motor LeftDrive2 = motor(PORT1, gearSetting::ratio6_1, false);
motor_group LeftDrive = motor_group(LeftDrive1, LeftDrive2);

motor RightDrive1 = motor(PORT2, gearSetting::ratio6_1, true);
motor RightDrive2 = motor(PORT2, gearSetting::ratio6_1, true);
motor_group RightDrive = motor_group(RightDrive1, RightDrive2);

drivetrain chassis = drivetrain(LeftDrive, RightDrive, 320, 320, 130, distanceUnits::mm, 1.0);


motor ArmMotor = motor(PORT3, gearSetting::ratio36_1, false);
motor ClawMotor = motor(PORT4, gearSetting::ratio18_1, false);

brain Brain;

  
void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  chassis.drive(forward);
  wait(2, seconds);
  chassis.drive(reverse);
  wait(2, seconds);
  chassis.stop();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  LeftDrive.setStopping(coast);
  RightDrive.setStopping(coast);
  ArmMotor.setVelocity(50, percentUnits::pct);
  ClawMotor.setVelocity(50, percentUnits::pct);

  while (1) {
    LeftDrive.spin(forward, Controller1.Axis3.position(), percentUnits::pct);
    RightDrive.spin(forward, Controller1.Axis2.position(), percentUnits::pct);

    if(Controller1.ButtonA.pressing()){
      ArmMotor.spin(forward);
    }
    else  if(Controller1.ButtonB.pressing()){
      ArmMotor.spin(reverse);
    }
    else{
      ArmMotor.stop(hold);
    }
    
    if(Controller1.ButtonL1.pressing()){
      ClawMotor.spin(forward);
    }
    else  if(Controller1.ButtonL2.pressing()){
      ClawMotor.spin(reverse);
    }
    else{
      ClawMotor.stop(hold);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
