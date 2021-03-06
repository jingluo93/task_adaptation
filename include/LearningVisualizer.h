#ifndef LEARNINGVISUALIZER_H
#define LEARNINGVISUALIZER_H


#include "ros/ros.h"

#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Float64.h"

#include "visualization_msgs/Marker.h"
#include "geometry_msgs/PointStamped.h"

#include <sensor_msgs/PointCloud.h>

#include "geometry_msgs/TwistStamped.h"

#include "nav_msgs/Path.h"


class LearningVisualizer {

private:

	// ros variables
	ros::NodeHandle nh_;
	ros::Rate loop_rate_;


	std::string topic_real_position_;
	std::string topic_beliefs_;
	std::string topic_betas_;

	std::vector<double> Beliefs_;

	std::vector<double> target_pose_1_;
	std::vector<double> target_pose_2_;
	std::vector<double> target_pose_3_;
	std::vector<double> target_pose_4_;

	ros::Subscriber sub_realPosition_;

	ros::Subscriber sub_target_1_;
	ros::Subscriber sub_target_2_;
	ros::Subscriber sub_target_3_;
	ros::Subscriber sub_target_4_;

	std::string topic_task1_velocity_;
	std::string topic_task2_velocity_;
	std::string topic_task3_velocity_;
	std::string topic_task4_velocity_;

	ros::Subscriber sub_task1_velocity_;
	ros::Subscriber sub_task2_velocity_;
	ros::Subscriber sub_task3_velocity_;
	ros::Subscriber sub_task4_velocity_;

	std::vector<float> Task1_velocity_;
	std::vector<float> Task2_velocity_;
	std::vector<float> Task3_velocity_;
	std::vector<float> Task4_velocity_;

	ros::Subscriber sub_beliefs_;
	ros::Subscriber sub_beta_;
	ros::Subscriber sub_alpha2_;


	ros::Publisher pub_surface_;

	ros::Publisher pub_marker_1_;
	ros::Publisher pub_marker_2_;
	ros::Publisher pub_marker_3_;
	ros::Publisher pub_marker_4_;


	sensor_msgs::PointCloud myPointCloud_;
	sensor_msgs::ChannelFloat32 myColorChannel;
	ros::Publisher pub_pointCloud_;


	visualization_msgs::Marker marker_1_;
	visualization_msgs::Marker marker_2_;
	visualization_msgs::Marker marker_3_;
	visualization_msgs::Marker marker_4_;

	visualization_msgs::Marker surface_;


	std::vector<double> x_lim_;
	std::vector<double> y_lim_;
	std::vector<double> z_lim_;
	std::vector<int> N_grid_xyz_;


	// task learning variables
	int N_centeriods_;
	std::vector<std::vector<double>> Centers_;
	std::vector<std::vector<double>> activations_;  // for each cloud-point vs each basis-fucntion
	std::vector<std::vector<double>> Beta_;
	std::vector<std::vector<double>> BeliefCloud_;


	double alpha2_;


	// future path
	std::vector<double> RealPosition_;

	nav_msgs::Path msg_DesiredPath_;
	int MAX_FRAME = 5;

	ros::Publisher pub_DesiredPath_;



public:

	LearningVisualizer(ros::NodeHandle &n,
	                   double frequency,
	                   std::string topic_real_position,
	                   std::string topic_beliefs,
	                   std::string topic_betas,
	                   std::vector<double> x_lim,
	                   std::vector<double> y_lim,
	                   std::vector<double> z_lim,
	                   std::vector<int> N_grid_xyz,
	                   std::string topic_task1_velocity,
	                   std::string topic_task2_velocity,
	                   std::string topic_task3_velocity,
	                   std::string topic_task4_velocity );

	bool Init();

	void Run();


private:




	void InitClassVariables();
	bool InitROS();

	void ComputeActivation();
	void ComputeBeliefs();

	// void ComputeDesiredVelocity();

	void UpdateVisualization();


	void updateRealPosition(const geometry_msgs::Pose::ConstPtr& msg);

	void GetTargetTask1(const geometry_msgs::PointStamped::ConstPtr& msg);
	void GetTargetTask2(const geometry_msgs::PointStamped::ConstPtr& msg);
	void GetTargetTask3(const geometry_msgs::PointStamped::ConstPtr& msg);
	void GetTargetTask4(const geometry_msgs::PointStamped::ConstPtr& msg);

	void UpdateBeliefs(const std_msgs::Float64MultiArray::ConstPtr& msg);
	void UpdateBetas(const std_msgs::Float64MultiArray::ConstPtr& msg);
	void UpdateAlpha2(const std_msgs::Float64::ConstPtr& msg);

	void UpdateTask1(const geometry_msgs::TwistStamped::ConstPtr& msg);
	void UpdateTask2(const geometry_msgs::TwistStamped::ConstPtr& msg);
	void UpdateTask3(const geometry_msgs::TwistStamped::ConstPtr& msg);
	void UpdateTask4(const geometry_msgs::TwistStamped::ConstPtr& msg);

	void ComputePublishFuturePath();

	// void DynCallback(task_adaptation::task_learning_paramsConfig& config, uint32_t level);
// 	// void UpdateParamCallback(const task_adaptation::task_adaptation_params::ConstPtr _msg);

};

#endif // LEARNINGVISUALIZER_H
