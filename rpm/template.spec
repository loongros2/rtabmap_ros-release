Name:           ros-lunar-rtabmap-ros
Version:        0.17.0
Release:        1%{?dist}
Summary:        ROS rtabmap_ros package

Group:          Development/Libraries
License:        BSD
Source0:        %{name}-%{version}.tar.gz

Requires:       ros-lunar-class-loader
Requires:       ros-lunar-compressed-depth-image-transport
Requires:       ros-lunar-compressed-image-transport
Requires:       ros-lunar-costmap-2d
Requires:       ros-lunar-cv-bridge
Requires:       ros-lunar-dynamic-reconfigure
Requires:       ros-lunar-eigen-conversions
Requires:       ros-lunar-geometry-msgs
Requires:       ros-lunar-image-geometry
Requires:       ros-lunar-image-transport
Requires:       ros-lunar-laser-geometry
Requires:       ros-lunar-message-filters
Requires:       ros-lunar-move-base-msgs
Requires:       ros-lunar-nav-msgs
Requires:       ros-lunar-nodelet
Requires:       ros-lunar-octomap-ros
Requires:       ros-lunar-pcl-conversions
Requires:       ros-lunar-pcl-ros
Requires:       ros-lunar-roscpp
Requires:       ros-lunar-rospy
Requires:       ros-lunar-rtabmap
Requires:       ros-lunar-rviz
Requires:       ros-lunar-sensor-msgs
Requires:       ros-lunar-std-msgs
Requires:       ros-lunar-std-srvs
Requires:       ros-lunar-stereo-msgs
Requires:       ros-lunar-tf
Requires:       ros-lunar-tf-conversions
Requires:       ros-lunar-tf2-ros
Requires:       ros-lunar-visualization-msgs
BuildRequires:  pcl-devel
BuildRequires:  ros-lunar-catkin
BuildRequires:  ros-lunar-class-loader
BuildRequires:  ros-lunar-costmap-2d
BuildRequires:  ros-lunar-cv-bridge
BuildRequires:  ros-lunar-dynamic-reconfigure
BuildRequires:  ros-lunar-eigen-conversions
BuildRequires:  ros-lunar-genmsg
BuildRequires:  ros-lunar-geometry-msgs
BuildRequires:  ros-lunar-image-geometry
BuildRequires:  ros-lunar-image-transport
BuildRequires:  ros-lunar-laser-geometry
BuildRequires:  ros-lunar-message-filters
BuildRequires:  ros-lunar-move-base-msgs
BuildRequires:  ros-lunar-nav-msgs
BuildRequires:  ros-lunar-nodelet
BuildRequires:  ros-lunar-octomap-ros
BuildRequires:  ros-lunar-pcl-conversions
BuildRequires:  ros-lunar-pcl-ros
BuildRequires:  ros-lunar-roscpp
BuildRequires:  ros-lunar-rospy
BuildRequires:  ros-lunar-rtabmap
BuildRequires:  ros-lunar-rviz
BuildRequires:  ros-lunar-sensor-msgs
BuildRequires:  ros-lunar-std-msgs
BuildRequires:  ros-lunar-std-srvs
BuildRequires:  ros-lunar-stereo-msgs
BuildRequires:  ros-lunar-tf
BuildRequires:  ros-lunar-tf-conversions
BuildRequires:  ros-lunar-tf2-ros
BuildRequires:  ros-lunar-visualization-msgs

%description
RTAB-Map's ros-pkg. RTAB-Map is a RGB-D SLAM approach with real-time
constraints.

%prep
%setup -q

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/lunar/setup.sh" ]; then . "/opt/ros/lunar/setup.sh"; fi
mkdir -p obj-%{_target_platform} && cd obj-%{_target_platform}
%cmake .. \
        -UINCLUDE_INSTALL_DIR \
        -ULIB_INSTALL_DIR \
        -USYSCONF_INSTALL_DIR \
        -USHARE_INSTALL_PREFIX \
        -ULIB_SUFFIX \
        -DCMAKE_INSTALL_LIBDIR="lib" \
        -DCMAKE_INSTALL_PREFIX="/opt/ros/lunar" \
        -DCMAKE_PREFIX_PATH="/opt/ros/lunar" \
        -DSETUPTOOLS_DEB_LAYOUT=OFF \
        -DCATKIN_BUILD_BINARY_PACKAGE="1" \

make %{?_smp_mflags}

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree that was dropped by catkin, and source it.  It will
# set things like CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/lunar/setup.sh" ]; then . "/opt/ros/lunar/setup.sh"; fi
cd obj-%{_target_platform}
make %{?_smp_mflags} install DESTDIR=%{buildroot}

%files
/opt/ros/lunar

%changelog
* Wed May 02 2018 Mathieu Labbe <matlabbe@gmail.com> - 0.17.0-1
- Autogenerated by Bloom

* Tue May 01 2018 Mathieu Labbe <matlabbe@gmail.com> - 0.17.0-0
- Autogenerated by Bloom

* Thu Aug 03 2017 Mathieu Labbe <matlabbe@gmail.com> - 0.13.2-0
- Autogenerated by Bloom

