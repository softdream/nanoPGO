#include "read_graph_data.h"

#include "nano_pgo.hpp"

#include <vector>
#include <map>

#include "utils.h"
#include <chrono>

int main()
{
	std::cout<<"------------------ POSE GRAPH TEST ------------------"<<std::endl;
	simulation::ReadGraphData simu;
	simu.openEdgeFile( "../../data/killian-e.dat" );
	simu.openVertexFile( "../../data/killian-v.dat" );


	pgo::GraphOptimizer<double> pgo;

	while( simu.getEdgeCount() < 3995 ){
		int id_from = 0;
		int id_to = 0;
		Eigen::Vector3d mean( 0.0, 0.0, 0.0 );
		Eigen::Matrix3d info_matrix = Eigen::Matrix3d::Zero();
		
		simu.readAEdge( id_from, id_to, mean, info_matrix );
		
		// add a edge
		pgo.addEdge( mean, id_from, id_to, info_matrix );		

	}

	while( simu.getVertexCount() < 1941 ){
		int vertex_id = 0;
		Eigen::Vector3d pose( 0.0, 0.0, 0.0 );
		
		simu.readAVertex( vertex_id, pose );
		
		// add a vertex
		pgo.addVertex( pose, vertex_id );
	}

	// before optimization
	std::vector<Eigen::Vector3d> vertex_poses = pgo.getReultVertexPosesVector();
	Utils::displayVertexPoses( vertex_poses );

	auto before_time = std::chrono::steady_clock::now();
	pgo.execuGraphOptimization( 2 );
	auto after_time = std::chrono::steady_clock::now();
	double duration_millsecond = std::chrono::duration<double, std::milli>(after_time - before_time).count();
        std::cout<<"duration : " << duration_millsecond << "ms" << std::endl;

	// after optimization
	vertex_poses = pgo.getReultVertexPosesVector();

	Utils::displayVertexPoses( vertex_poses );
	
	return 0;
}
