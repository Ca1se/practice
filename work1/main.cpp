/*
	Modify from Games101 assignment1
*/

#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0],
				 0, 1, 0, -eye_pos[1],
				 0, 0, 1, -eye_pos[2],
				 0, 0, 0, 1;
    return translate * view;
}


Eigen::Matrix4f get_model_matrix(const Eigen::Vector3f& center_point, Eigen::Vector3f rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f x_rotation, y_rotation, z_rotation, translation, t_translation;
	
	rotation_angle.x() = rotation_angle.x() / 180 * MY_PI;
    rotation_angle.y() = rotation_angle.y() / 180 * MY_PI;
    rotation_angle.z() = rotation_angle.z() / 180 * MY_PI;

	translation << 1, 0, 0, -center_point[0],
				   0, 1, 0, -center_point[1],
				   0, 0, 1, -center_point[2],
				   0, 0, 0, 1;

	t_translation << 1, 0, 0, center_point[0],
	                 0, 1, 0, center_point[1],
	                 0, 0, 1, center_point[2],
	                 0, 0, 0, 1;

	x_rotation << 1, 0, 0, 0,
			      0, cos(rotation_angle[0]), -sin(rotation_angle[0]), 0,
				  0, sin(rotation_angle[0]),  cos(rotation_angle[0]), 0,
				  0, 0, 0, 1;

	y_rotation << cos(rotation_angle[1]), 0, sin(rotation_angle[1]), 0,
			      0, 1, 0, 0,
				  -sin(rotation_angle[1]), 0, cos(rotation_angle[1]), 0,
				  0, 0, 0, 1;
	
    z_rotation << cos(rotation_angle[2]), -sin(rotation_angle[2]), 0, 0,
				  sin(rotation_angle[2]),  cos(rotation_angle[2]), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1;

    return t_translation * x_rotation * y_rotation * z_rotation * translation * model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f perspective_part;
    Eigen::Matrix4f orthographic_part;

    perspective_part << zNear, 0, 0, 0,
                        0, zNear, 0, 0,
                        0, 0, zNear + zFar, -zNear * zFar,
                        0, 0, 1, 0;

    float top = -tan(eye_fov / 180 * MY_PI / 2) * zNear;
    float bottom = -top;
    float left = bottom * aspect_ratio;
    float right = -left;
    orthographic_part << 2.0f / (right - left), 0, 0, -(right + left) / (right - left),
                         0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom),
                         0, 0, 2.0f / (zNear - zFar), -(zNear + zFar) / (zNear - zFar),
                         0, 0, 0, 1;
    projection = orthographic_part * perspective_part * projection;

    return projection;
}

int main(int argc, const char** argv)
{
	Eigen::Vector3f angle{0, 0, 0};
    bool command_line = false;
    std::string filename = "output.png";

	/*
    if (argc >= 3) {
        command_line = true;
        angle = std::stof(argv[2]); // -r by default
        if (argc == 4) {
            filename = std::string(argv[3]);
        }
        else if(argc > 4)
            return 0;
    }
	*/

    rst::rasterizer r(700, 700);

	// triangle
	/*
    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};
	*/

	// cube
	Eigen::Vector3f eye_pos = {0, 0, 8};
	
	std::vector<Eigen::Vector3f> pos{{1, 1, -2}, {1, -1, -2}, {-1, -1, -2}, {-1, 1, -2},
									 {1, 1, -4}, {1, -1, -4}, {-1, -1, -4}, {-1, 1, -4}};

	std::vector<std::vector<int>> indices{{0, 1, 2, 3, 4, 5, 6, 7}};

    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(indices);

    int key = 0;
    int frame_count = 0;

	float eye_fov = 45;
	float aspect_ratio = 1;
	float zNear = -0.1;
	float zFar = -50;

	/*
    if (command_line) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(eye_fov, aspect_ratio, zNear, zFar));

        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);

        cv::imwrite(filename, image);

        return 0;
    }
	*/

    while (key != 27) {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        r.set_model(get_model_matrix(Eigen::Vector3f{0, 0, -3}, angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(eye_fov, aspect_ratio, zNear, zFar));

        r.draw(pos_id, ind_id, rst::Primitive::Cube);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(0);

        std::cout << "frame count: " << frame_count++ << '\n';

        if (key == 'a') {
            angle[1] += 3;
        }else if (key == 'd') {
            angle[1] -= 3;
        }else if (key == 'w') {
			angle[0] += 3;
		}else if (key == 's') {
			angle[0] -= 3;
		}else if (key == 'q') {
			angle[2] += 3;
		}else if (key == 'e') {
			angle[2] -= 3;
		}
    }

    return 0;
}
