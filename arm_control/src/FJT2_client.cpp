#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

typedef  actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> TrajClient;


class RobotArm
{
private:
  TrajClient* traj_client_;

public:
  RobotArm() : traj_client_(NULL)
  {
    if ( not traj_client_ )
      traj_client_ = new TrajClient("arm_controller/follow_joint_trajectory", true);

    while(!traj_client_->waitForServer(ros::Duration(5.0))){
      ROS_WARN("Waiting for the joint_trajectory server");
    }
  
    ROS_INFO("Connected to joint_trajectory server");
  }

  ~RobotArm()
  {
    if ( traj_client_ )
      delete traj_client_;
  }


  void startTrajectory(control_msgs::FollowJointTrajectoryGoal goal)
  {  
    goal.trajectory.header.stamp = ros::Time::now() + ros::Duration(1.0);
    traj_client_->sendGoal(goal);
  }


  control_msgs::FollowJointTrajectoryGoal armExtensionTrajectory()
  {
    //our goal variable
    control_msgs::FollowJointTrajectoryGoal goal;

    // First, the joint names, which apply to all waypoints
    goal.trajectory.joint_names.push_back("base");
    goal.trajectory.joint_names.push_back("elbow");
    goal.trajectory.joint_names.push_back("gripper");
      
    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.resize(1);

    // First trajectory point
    // Positions
    int ind = 0;
    goal.trajectory.points[ind].positions.resize(3);
    goal.trajectory.points[ind].positions[0] = -1.7;
    goal.trajectory.points[ind].positions[1] = 2.5;
    goal.trajectory.points[ind].positions[2] = -2.4;
    
    // Velocities
    goal.trajectory.points[ind].velocities.resize(3);
    for (size_t j = 0; j < 3; ++j)
      {
	goal.trajectory.points[ind].velocities[j] = 0.0;
      }
    // To be reached 1 second after starting along the trajectory
    goal.trajectory.points[ind].time_from_start = ros::Duration(2.0);

    // Second trajectory point
    // Positions
   /* ind += 1;
    goal.trajectory.points[ind].positions.resize(3);
    goal.trajectory.points[ind].positions[0] = 1.5;
    goal.trajectory.points[ind].positions[1] = 1.5;
    goal.trajectory.points[ind].positions[2] = -0.6;
  
    // Velocities
    goal.trajectory.points[ind].velocities.resize(3);
    for (size_t j = 0; j < 3; ++j)
      {
	goal.trajectory.points[ind].velocities[j] = 0.0;
      }
    // To be reached 2 seconds after starting along the trajectory
    goal.trajectory.points[ind].time_from_start = ros::Duration(8.0);
*/
    //we are done; return the goal
    return goal;
  }

  //! Returns the current state of the action
  actionlib::SimpleClientGoalState getState()
  {
    return traj_client_->getState();
  }
 
};

int main(int argc, char** argv)
{
  // Init the ROS node
  ros::init(argc, argv, "robot_driver");

  RobotArm arm;
  
  // Start the trajectory
 {  arm.startTrajectory(arm.armExtensionTrajectory());}
 
  // Wait for trajectory completion
  while(!arm.getState().isDone() && ros::ok())
    {
      usleep(50000);
    }
}
