%bcond_without tests
%bcond_without weak_deps

%global __os_install_post %(echo '%{__os_install_post}' | sed -e 's!/usr/lib[^[:space:]]*/brp-python-bytecompile[[:space:]].*$!!g')
%global __provides_exclude_from ^/opt/ros/iron/.*$
%global __requires_exclude_from ^/opt/ros/iron/.*$

Name:           ros-iron-rtabmap-slam
Version:        0.21.2
Release:        1%{?dist}%{?release_suffix}
Summary:        ROS rtabmap_slam package

License:        BSD
Source0:        %{name}-%{version}.tar.gz

Requires:       ros-iron-cv-bridge
Requires:       ros-iron-geometry-msgs
Requires:       ros-iron-nav-msgs
Requires:       ros-iron-nav2-msgs
Requires:       ros-iron-rclcpp
Requires:       ros-iron-rclcpp-components
Requires:       ros-iron-rtabmap-msgs
Requires:       ros-iron-rtabmap-sync
Requires:       ros-iron-rtabmap-util
Requires:       ros-iron-sensor-msgs
Requires:       ros-iron-std-msgs
Requires:       ros-iron-std-srvs
Requires:       ros-iron-tf2
Requires:       ros-iron-tf2-ros
Requires:       ros-iron-visualization-msgs
Requires:       ros-iron-ros-workspace
BuildRequires:  ros-iron-ament-cmake-ros
BuildRequires:  ros-iron-cv-bridge
BuildRequires:  ros-iron-geometry-msgs
BuildRequires:  ros-iron-nav-msgs
BuildRequires:  ros-iron-nav2-msgs
BuildRequires:  ros-iron-rclcpp
BuildRequires:  ros-iron-rclcpp-components
BuildRequires:  ros-iron-rtabmap-msgs
BuildRequires:  ros-iron-rtabmap-sync
BuildRequires:  ros-iron-rtabmap-util
BuildRequires:  ros-iron-sensor-msgs
BuildRequires:  ros-iron-std-msgs
BuildRequires:  ros-iron-std-srvs
BuildRequires:  ros-iron-tf2
BuildRequires:  ros-iron-tf2-ros
BuildRequires:  ros-iron-visualization-msgs
BuildRequires:  ros-iron-ros-workspace
Provides:       %{name}-devel = %{version}-%{release}
Provides:       %{name}-doc = %{version}-%{release}
Provides:       %{name}-runtime = %{version}-%{release}

%description
RTAB-Map's SLAM package.

%prep
%autosetup -p1

%build
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/iron/setup.sh" ]; then . "/opt/ros/iron/setup.sh"; fi
mkdir -p .obj-%{_target_platform} && cd .obj-%{_target_platform}
%cmake3 \
    -UINCLUDE_INSTALL_DIR \
    -ULIB_INSTALL_DIR \
    -USYSCONF_INSTALL_DIR \
    -USHARE_INSTALL_PREFIX \
    -ULIB_SUFFIX \
    -DCMAKE_INSTALL_PREFIX="/opt/ros/iron" \
    -DAMENT_PREFIX_PATH="/opt/ros/iron" \
    -DCMAKE_PREFIX_PATH="/opt/ros/iron" \
    -DSETUPTOOLS_DEB_LAYOUT=OFF \
%if !0%{?with_tests}
    -DBUILD_TESTING=OFF \
%endif
    ..

%make_build

%install
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/iron/setup.sh" ]; then . "/opt/ros/iron/setup.sh"; fi
%make_install -C .obj-%{_target_platform}

%if 0%{?with_tests}
%check
# Look for a Makefile target with a name indicating that it runs tests
TEST_TARGET=$(%__make -qp -C .obj-%{_target_platform} | sed "s/^\(test\|check\):.*/\\1/;t f;d;:f;q0")
if [ -n "$TEST_TARGET" ]; then
# In case we're installing to a non-standard location, look for a setup.sh
# in the install tree and source it.  It will set things like
# CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, and PYTHONPATH.
if [ -f "/opt/ros/iron/setup.sh" ]; then . "/opt/ros/iron/setup.sh"; fi
CTEST_OUTPUT_ON_FAILURE=1 \
    %make_build -C .obj-%{_target_platform} $TEST_TARGET || echo "RPM TESTS FAILED"
else echo "RPM TESTS SKIPPED"; fi
%endif

%files
/opt/ros/iron

%changelog
* Sat Aug 05 2023 Mathieu Labbe <matlabbe@gmail.com> - 0.21.2-1
- Autogenerated by Bloom

