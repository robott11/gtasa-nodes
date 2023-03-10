#include <string>
#include "CNode.h"
#include "Exceptions/FileNotFoundException.h"

CNode::CNode(std::string &nodeFile)
{
    CNode::mFilePath = nodeFile;
    CNode::mNodeFile = std::ifstream(nodeFile, std::ios::binary);

    if (!CNode::mNodeFile.is_open()) {
        throw FileNotFoundException(nodeFile.c_str());
    }
}

void CNode::getHeader()
{
    std::cout << "======= HEADER =======" << std::endl;
    std::cout << "PATH NODES: " << CNode::mHeader.pathNodes << std::endl;
    std::cout << "VEHICLE NODES: " << CNode::mHeader.vehicleNodes << std::endl;
    std::cout << "PED NODES: " << CNode::mHeader.pedNodes << std::endl;
    std::cout << "NAVI NODES: " << CNode::mHeader.naviNodes << std::endl;
    std::cout << "LINKS: " << CNode::mHeader.links << std::endl << std::endl;
}

void CNode::getNodes()
{
    for (sPathNodeEntry pathNode : CNode::mVehicleNodes) {
        std::cout << "======= VEHICLE NODE ID #" << pathNode.nodeID << " =======" << std::endl;
        std::cout << "NODE LINK ID #" << pathNode.linkID << std::endl;
        std::cout << "NODE AREA ID #" << pathNode.areaID << std::endl;
        std::cout << "NODE POSITION: " << pathNode.position[0] / 8 << " " << pathNode.position[1] / 8 << " " << pathNode.position[2] / 8 << std::endl;
        std::cout << "NODE COST: 0x" << std::hex << pathNode.cost << std::dec << std::endl;
        std::cout << std::endl;
    }

    for (sPathNodeEntry pathNode : CNode::mPedNodes) {
        std::cout << "======= PED NODE ID #" << pathNode.nodeID << " =======" << std::endl;
        std::cout << "NODE LINK ID #" << pathNode.linkID << std::endl;
        std::cout << "NODE AREA ID #" << pathNode.areaID << std::endl;
        std::cout << "NODE POSITION: " << pathNode.position[0] / 8 << " " << pathNode.position[1] / 8 << " " << pathNode.position[2] / 8 << std::endl;
        std::cout << "NODE COST: 0x" << std::hex << pathNode.cost << std::dec << std::endl;
        std::cout << std::endl;
    }
}

CNode *CNode::read()
{
    mNodeFile.seekg(0);
    mNodeFile.read((char*) &mHeader, sizeof(mHeader));

    for (size_t i = 1; i <= CNode::mHeader.vehicleNodes; i++) {
        sPathNodeEntry tempPathNode;

        CNode::mNodeFile.read((char*) &tempPathNode, sizeof(tempPathNode));
        CNode::mVehicleNodes.push_back(tempPathNode);
    }

    for (size_t i = 1; i <= CNode::mHeader.pedNodes; i++) {
        sPathNodeEntry tempPathNode;

        CNode::mNodeFile.read((char*) &tempPathNode, sizeof(tempPathNode));
        CNode::mPedNodes.push_back(tempPathNode);
    }

    return this;
}
