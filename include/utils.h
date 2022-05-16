#ifndef __UTILS_H
#define __UTILS_H

#include <Eigen/Dense>

#include <opencv2/opencv.hpp>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200

class Utils
{
public:
	template<typename T>
	static void displayVertexPoses( const std::vector<Eigen::Matrix<T, 3, 1>> &vertex_poses, const std::string &window_name = "vertex", const T scale = 2.5 );

};

template<typename T>
void Utils::displayVertexPoses( const std::vector<Eigen::Matrix<T, 3, 1>> &vertex_poses, const std::string &window_name, const T scale )
        {
                cv::Mat image = cv::Mat::zeros( WINDOW_WIDTH, WINDOW_HEIGHT, CV_8UC3 );
                cv::line( image, cv::Point( WINDOW_WIDTH / 2, 0 ), cv::Point( WINDOW_WIDTH / 2, WINDOW_HEIGHT ), cv::Scalar( 67, 128, 94 ), 1 );
                cv::line( image, cv::Point( 0, WINDOW_HEIGHT / 2 ), cv::Point( WINDOW_WIDTH, WINDOW_HEIGHT / 2 ), cv::Scalar( 67, 128, 94 ), 1 );

                if( vertex_poses.empty() ){
                        return;
                }

                for( auto it : vertex_poses ){
                        cv::Point2d point( it[0] * scale + WINDOW_WIDTH / 2, it[1] * scale + WINDOW_HEIGHT / 2 );
                        cv::circle(image, point, 1, cv::Scalar(0, 0, 255), -1);   
                }

                cv::imshow( window_name, image );
                cv::waitKey( 0 );
        }


#endif
