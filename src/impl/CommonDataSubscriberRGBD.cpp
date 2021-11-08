/*
Copyright (c) 2010-2016, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <rtabmap_ros/CommonDataSubscriber.h>
#include <rtabmap/utilite/UConversion.h>
#include <rtabmap/core/Compression.h>
#include <rtabmap_ros/MsgConversion.h>
#include <cv_bridge/cv_bridge.h>

namespace rtabmap_ros {

// 1 RGBD camera
void CommonDataSubscriber::rgbdCallback(
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdScan2dCallback(
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::LaserScan::ConstSharedPtr scanMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			*scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdScan3dCallback(
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::PointCloud2::ConstSharedPtr scan3dMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, *scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdScanDescCallback(
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::ScanDescriptor::ConstSharedPtr scanDescMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg; // Null
	nav_msgs::msg::Odometry::ConstSharedPtr odomMsg; // Null
	rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanDescMsg->scan, scanDescMsg->scan_cloud, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdInfoCallback(
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}

// 1 RGBD camera + Odom
void CommonDataSubscriber::rgbdOdomCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomScan2dCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::LaserScan::ConstSharedPtr scanMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			*scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomScan3dCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::PointCloud2::ConstSharedPtr scan3dMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, *scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomScanDescCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::ScanDescriptor::ConstSharedPtr scanDescMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg; // Null
	rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}
	if(!scanDescMsg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(scanDescMsg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanDescMsg->scan, scanDescMsg->scan_cloud, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomInfoCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::UserData::SharedPtr userDataMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}

#ifdef RTABMAP_SYNC_USER_DATA
// 1 RGBD camera + User Data
void CommonDataSubscriber::rgbdDataCallback(
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdDataScan2dCallback(
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::LaserScan::ConstSharedPtr scanMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			*scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdDataScan3dCallback(
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::PointCloud2::ConstSharedPtr scan3dMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	nav_msgs::msg::Odometry::SharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, *scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdDataScanDescCallback(
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::ScanDescriptor::ConstSharedPtr scanDescMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	nav_msgs::msg::Odometry::ConstSharedPtr odomMsg; // Null
	rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}
	if(!scanDescMsg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(scanDescMsg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanDescMsg->scan, scanDescMsg->scan_cloud, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdDataInfoCallback(
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	nav_msgs::msg::Odometry::ConstSharedPtr odomMsg; // Null
	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}

// 1 RGBD camera + Odom + User Data
void CommonDataSubscriber::rgbdOdomDataCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomDataScan2dCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::LaserScan::ConstSharedPtr scanMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			*scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomDataScan3dCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const sensor_msgs::msg::PointCloud2::ConstSharedPtr scan3dMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	sensor_msgs::msg::LaserScan scanMsg; // Null
	rtabmap_ros::msg::OdomInfo::SharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg ,rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, *scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomDataScanDescCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::ScanDescriptor::ConstSharedPtr scanDescMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg; // null

	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}
	if(!scanDescMsg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(scanDescMsg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg ,rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanDescMsg->scan, scanDescMsg->scan_cloud, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
void CommonDataSubscriber::rgbdOdomDataInfoCallback(
		const nav_msgs::msg::Odometry::ConstSharedPtr odomMsg,
		const rtabmap_ros::msg::UserData::ConstSharedPtr userDataMsg,
		const rtabmap_ros::msg::RGBDImage::ConstSharedPtr image1Msg,
		const rtabmap_ros::msg::OdomInfo::ConstSharedPtr odomInfoMsg)
{
	cv_bridge::CvImageConstPtr rgb, depth;
	rtabmap_ros::toCvShare(image1Msg, rgb, depth);

	sensor_msgs::msg::LaserScan scanMsg; // Null
	sensor_msgs::msg::PointCloud2 scan3dMsg; // Null
	std::vector<rtabmap_ros::msg::GlobalDescriptor> globalDescriptorMsgs;
	if(!image1Msg->global_descriptor.data.empty())
	{
		globalDescriptorMsgs.push_back(image1Msg->global_descriptor);
	}

	commonSingleDepthCallback(odomMsg, userDataMsg, rgb,
			depth, image1Msg->rgb_camera_info, image1Msg->depth_camera_info,
			scanMsg, scan3dMsg, odomInfoMsg,
			globalDescriptorMsgs, image1Msg->key_points, image1Msg->points,
			rtabmap::uncompressData(image1Msg->descriptors));
}
#endif

void CommonDataSubscriber::setupRGBDCallbacks(
		rclcpp::Node& node,
		bool subscribeOdom,
#ifdef RTABMAP_SYNC_USER_DATA
		bool subscribeUserData,
#else
		bool,
#endif
		bool subscribeScan2d,
		bool subscribeScan3d,
		bool subscribeScanDesc,
		bool subscribeOdomInfo,
		int queueSize,
		bool approxSync)
{
	RCLCPP_INFO(node.get_logger(), "Setup rgbd callback");

	if(subscribeOdom ||
#ifdef RTABMAP_SYNC_USER_DATA
	   subscribeUserData ||
#endif
	   subscribeScan2d ||
	   subscribeScan3d ||
	   subscribeScanDesc ||
	   subscribeOdomInfo)
	{
		rgbdSubs_.resize(1);
		rgbdSubs_[0] = new message_filters::Subscriber<rtabmap_ros::msg::RGBDImage>;
		rgbdSubs_[0]->subscribe(&node, "rgbd_image");

#ifdef RTABMAP_SYNC_USER_DATA
		if(subscribeOdom && subscribeUserData)
		{
			odomSub_.subscribe(&node, "odom");
			userDataSub_.subscribe(&node, "user_data");
			if(subscribeScanDesc)
			{
				subscribedToScanDescriptor_ = true;
				scanDescSub_.subscribe(&node, "scan_descriptor");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL4(CommonDataSubscriber, rgbdOdomDataScanDesc, approxSync, queueSize, odomSub_, userDataSub_, (*rgbdSubs_[0]), scanDescSub_);
			}
			else if(subscribeScan2d)
			{
				subscribedToScan2d_ = true;
				scanSub_.subscribe(&node, "scan");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL4(CommonDataSubscriber, rgbdOdomDataScan2d, approxSync, queueSize, odomSub_, userDataSub_, (*rgbdSubs_[0]), scanSub_);
			}
			else if(subscribeScan3d)
			{
				subscribedToScan3d_ = true;
				scan3dSub_.subscribe(&node, "scan_cloud");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL4(CommonDataSubscriber, rgbdOdomDataScan3d, approxSync, queueSize, odomSub_, userDataSub_, (*rgbdSubs_[0]), scan3dSub_);
			}
			else if(subscribeOdomInfo)
			{
				subscribedToOdomInfo_ = true;
				odomInfoSub_.subscribe(&node, "odom_info");
				SYNC_DECL4(CommonDataSubscriber, rgbdOdomDataInfo, approxSync, queueSize, odomSub_, userDataSub_, (*rgbdSubs_[0]), odomInfoSub_);
			}
			else
			{
				SYNC_DECL3(CommonDataSubscriber, rgbdOdomData, approxSync, queueSize, odomSub_, userDataSub_, (*rgbdSubs_[0]));
			}
		}
		else
#endif			
		if(subscribeOdom)
		{
			odomSub_.subscribe(&node, "odom");
			if(subscribeScanDesc)
			{
				subscribedToScanDescriptor_ = true;
				scanDescSub_.subscribe(&node, "scan_descriptor");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdOdomScanDesc, approxSync, queueSize, odomSub_, (*rgbdSubs_[0]), scanDescSub_);
			}
			else if(subscribeScan2d)
			{
				subscribedToScan2d_ = true;
				scanSub_.subscribe(&node, "scan");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdOdomScan2d, approxSync, queueSize, odomSub_, (*rgbdSubs_[0]), scanSub_);
			}
			else if(subscribeScan3d)
			{
				subscribedToScan3d_ = true;
				scan3dSub_.subscribe(&node, "scan_cloud");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdOdomScan3d, approxSync, queueSize, odomSub_, (*rgbdSubs_[0]), scan3dSub_);
			}
			else if(subscribeOdomInfo)
			{
				subscribedToOdomInfo_ = true;
				odomInfoSub_.subscribe(&node, "odom_info");
				SYNC_DECL3(CommonDataSubscriber, rgbdOdomInfo, approxSync, queueSize, odomSub_, (*rgbdSubs_[0]), odomInfoSub_);
			}
			else
			{
				SYNC_DECL2(CommonDataSubscriber, rgbdOdom, approxSync, queueSize, odomSub_, (*rgbdSubs_[0]));
			}
		}
#ifdef RTABMAP_SYNC_USER_DATA
		else if(subscribeUserData)
		{
			userDataSub_.subscribe(&node, "user_data");
			if(subscribeScanDesc)
			{
				subscribedToScanDescriptor_ = true;
				scanDescSub_.subscribe(&node, "scan_descriptor");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdDataScanDesc, approxSync, queueSize, userDataSub_, (*rgbdSubs_[0]), scanDescSub_);
			}
			else if(subscribeScan2d)
			{
				subscribedToScan2d_ = true;
				scanSub_.subscribe(&node, "scan");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdDataScan2d, approxSync, queueSize, userDataSub_, (*rgbdSubs_[0]), scanSub_);
			}
			else if(subscribeScan3d)
			{
				subscribedToScan3d_ = true;
				scan3dSub_.subscribe(&node, "scan_cloud");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL3(CommonDataSubscriber, rgbdDataScan3d, approxSync, queueSize, userDataSub_, (*rgbdSubs_[0]), scan3dSub_);
			}
			else if(subscribeOdomInfo)
			{
				subscribedToOdomInfo_ = true;
				odomInfoSub_.subscribe(&node, "odom_info");
				SYNC_DECL3(CommonDataSubscriber, rgbdDataInfo, approxSync, queueSize, userDataSub_, (*rgbdSubs_[0]), odomInfoSub_);
			}
			else
			{
				SYNC_DECL2(CommonDataSubscriber, rgbdData, approxSync, queueSize, userDataSub_, (*rgbdSubs_[0]));
			}
		}
#endif
		else
		{
			if(subscribeScanDesc)
			{
				subscribedToScanDescriptor_ = true;
				scanDescSub_.subscribe(&node, "scan_descriptor");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL2(CommonDataSubscriber, rgbdScanDesc, approxSync, queueSize, (*rgbdSubs_[0]), scanDescSub_);
			}
			else if(subscribeScan2d)
			{
				subscribedToScan2d_ = true;
				scanSub_.subscribe(&node, "scan");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL2(CommonDataSubscriber, rgbdScan2d, approxSync, queueSize, (*rgbdSubs_[0]), scanSub_);
			}
			else if(subscribeScan3d)
			{
				subscribedToScan3d_ = true;
				scan3dSub_.subscribe(&node, "scan_cloud");
				if(subscribeOdomInfo)
				{
					subscribedToOdomInfo_ = false;
					RCLCPP_WARN(node.get_logger(),  "subscribe_odom_info ignored...");
				}
				SYNC_DECL2(CommonDataSubscriber, rgbdScan3d, approxSync, queueSize, (*rgbdSubs_[0]), scan3dSub_);
			}
			else if(subscribeOdomInfo)
			{
				subscribedToOdomInfo_ = true;
				odomInfoSub_.subscribe(&node, "odom_info");
				SYNC_DECL2(CommonDataSubscriber, rgbdInfo, approxSync, queueSize, (*rgbdSubs_[0]), odomInfoSub_);
			}
			else
			{
				UFATAL("Not supposed to be here!");
			}
		}
	}
	else
	{
		rgbdSub_ = node.create_subscription<rtabmap_ros::msg::RGBDImage>("rgbd_image", 5, std::bind(&CommonDataSubscriber::rgbdCallback, this, std::placeholders::_1));

		subscribedTopicsMsg_ =
				uFormat("\n%s subscribed to:\n   %s",
				node.get_name(),
				rgbdSub_->get_topic_name());
	}
}

} /* namespace rtabmap_ros */
