﻿#include "node.h"
#include <opencv2/opencv.hpp>

using namespace qv;

FindLineNode::FindLineNode(void* _parent) : NodeBase(_parent)
{
    name = "FindLineNode";
    description = u8"查找直线";
    nodeID = 400002;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputLine);

    IPreprocess = rv::IPreprocess::create();

}

std::string qv::FindLineNode::className() const
{
    return "FindLine";
}

std::string qv::FindLineNode::displayName() const
{
    return u8"直线查找";
}

RunStatus FindLineNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }


        runResult.isOk = true;

        //保存参数
        //Variant* outputVariant = getOutputSource(outputImage);
        //if (outputVariant != nullptr)
        //{
        //    outputVariant->setValue(dst);
        //}

        //设置显示图像
        if (rewindow != nullptr)
        {
            
        }

        runResult.message = u8"OK";
        runResult.result = RunResult::Accept;
    }
    catch (const std::exception& ex)
    {
        runResult.message = std::string(ex.what());
        runResult.result = RunResult::Error;
    }
    runResult.totalTime = totalTimer.elapsed() * 1000.0;

    return runResult;
}
