import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import Command, LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
 

def generate_launch_description():
    package_share = get_package_share_directory("bumperbot_description")
    default_model_path = os.path.join(package_share, "urdf", "bumperbot.urdf.xacro")
    default_rviz_config_path = os.path.join(package_share, "rviz", "display.rviz")

    model_arg = DeclareLaunchArgument(
        name="model",
        default_value=default_model_path,
        description="Absolute path to the robot URDF/Xacro file",
    )

    robot_description = ParameterValue(
        Command(["xacro ", LaunchConfiguration("model")]),
        value_type=str,
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": robot_description}],
    )

    joint_state_publisher = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
    )

    rviz2 = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen",
        arguments=["-d", default_rviz_config_path],
    )

    return LaunchDescription(
        [
            model_arg,
            joint_state_publisher,
            robot_state_publisher,
            rviz2,
        ]
    )
