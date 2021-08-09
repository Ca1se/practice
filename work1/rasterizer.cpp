//
// Created by goksu on 4/6/19.
//

#include <algorithm>
#include "rasterizer.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <stdexcept>


rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f>& positions)
{
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<std::vector<int>>& indices)
{
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return {id};
}

void rst::rasterizer::draw_line(const Eigen::Vector3f& begin, const Eigen::Vector3f& end)
{
	int x_begin = begin.x();
	int x_end = end.x();
	int y_begin = begin.y();
	int y_end = end.y();

    Eigen::Vector3f line_color = {255, 255, 255};

	if(x_end - x_begin < 0) {
		std::swap(x_begin, x_end);
		std::swap(y_begin, y_end);
	}

	int dx = x_end - x_begin;
	int dy = y_end - y_begin;
	int e, cy = dy < 0 ? -1 : 1;

	if(dx >= abs(dy)) {
		e = -dx;
		dy = abs(dy);
		for(int x = x_begin, y = y_begin; x != x_end; x++) {
			Eigen::Vector3f point(x, y, 1.0f);
			set_pixel(point, line_color);
			e += 2 * dy;
			if(e > 0) {
				e -= 2 * dx;
				y += cy;
			}
		}
	}else {
		e = -dy;
		dy = abs(dy);
		for(int x = x_begin, y = y_begin; y != y_end; y += cy) {
			Eigen::Vector3f point(x, y, 1.0f);
			set_pixel(point, line_color);
			e += 2 * dx;
			if(e > 0) {
				e -= 2 * dy;
				x++;
			}
		}
	}
	Eigen::Vector3f point(x_end, y_end, 1.0f);
	set_pixel(point, line_color);
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f)
{
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

void rst::rasterizer::draw(rst::pos_buf_id pos_buffer, rst::ind_buf_id ind_buffer, rst::Primitive type)
{
    if (type != rst::Primitive::Triangle && type != rst::Primitive::Cube)
    {
        throw std::runtime_error("Drawing primitives other than triangle is not implemented yet!");
    }
	const auto& buf = pos_buf[pos_buffer.pos_id];
    const auto& ind = ind_buf[ind_buffer.ind_id];

    float f1 = (100 - 0.1) / 2.0;
    float f2 = (100 + 0.1) / 2.0;

    Eigen::Matrix4f mvp = projection * view * model;

	if(type == rst::Primitive::Triangle) {
		Eigen::Vector4f v[3];
        
        for (const auto& i : ind)
        {
            Triangle t;

            for(int r = 0; r < 3; r++) {
				v[r] = mvp * to_vec4(buf[i[r]], 1.0f);
			}

            for (auto& vec : v) {
                vec /= vec.w();
            }

            for (auto & vert : v) {
                vert.x() = 0.5*width*(vert.x()+1.0);
                vert.y() = 0.5*height*(vert.y()+1.0);
                vert.z() = vert.z() * f1 + f2;
            }

            for (int i = 0; i < 3; ++i) {
                t.setVertex(i, v[i].head<3>());
            }
            rasterize_wireframe(t);
        }
	}else {
		std::vector<Eigen::Vector4f> v(8);
		std::vector<Eigen::Vector3f> sv;
		float min_z = 0x3f3f3f3f;

		for(const auto& index: ind) {
			int index_num = index.size();

			for(int i = 0; i < index_num; i++) {
				v[i] = mvp * to_vec4(buf[index[i]], 1.0f);
			}

			for(auto& vec: v) {
				vec /= vec.w();
			}

			for(auto& vert: v) {
				vert /= vert.w();
				vert.x() = 0.5*width*(vert.x()+1.0);
                vert.y() = 0.5*height*(vert.y()+1.0);
                vert.z() = vert.z() * f1 + f2;
				min_z = std::min(min_z, vert.z());
				sv.push_back(vert.head<3>());
			}

			rasterize_wireframe(sv, min_z);
		}
	}
}

void rst::rasterizer::rasterize_wireframe(const Triangle& t)
{
    draw_line(t.c(), t.a());
    draw_line(t.c(), t.b());
    draw_line(t.b(), t.a());
}

void rst::rasterizer::rasterize_wireframe(const std::vector<Eigen::Vector3f>& v, float min_z)
{
	int ind[][4] = {{0, 3, 1, 4}, {2, 1, 3, 6}, {5, 4, 6, 1}, {7, 6, 4, 3}};
	for(int i = 0; i < 4; i++) {
		if(min_z != v[ind[i][0]].z()) {
			for(int k = 1; k < 4; k++) {
				if(min_z != v[ind[i][k]].z()) {
					draw_line(v[ind[i][0]], v[ind[i][k]]);
				}
			}
		}
	}
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m)
{
    model = m;
}

void rst::rasterizer::set_view(const Eigen::Matrix4f& v)
{
    view = v;
}

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p)
{
    projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff)
{
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
    {
        std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
    }
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
}

int rst::rasterizer::get_index(int x, int y)
{
    return (height-y)*width + x;
}

void rst::rasterizer::set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color)
{
    //old index: auto ind = point.y() + point.x() * width;
    if (point.x() < 0 || point.x() >= width ||
        point.y() < 0 || point.y() >= height) return;
    auto ind = (height-point.y())*width + point.x();
    frame_buf[ind] = color;
}

