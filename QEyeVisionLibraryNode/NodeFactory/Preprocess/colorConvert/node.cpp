﻿#include "node.h"
#include <opencv2/opencv.hpp>

using namespace qv;

ColorConvertNode::ColorConvertNode(void* _parent) : NodeBase(_parent)
{
    name = "ColorConvertNode";
    description = "颜色转换";
    nodeID = 100004;
    isEnableRefer = false;

    inputs.push_back(inputImage);
    outputs.push_back(outputImage);

    IPreprocess = rv::IPreprocess::create();

}

std::string qv::ColorConvertNode::className() const
{
    return "ColorConvert";
}

std::string qv::ColorConvertNode::displayName() const
{
    return u8"颜色转换";
}

RunStatus ColorConvertNode::runImage(rv::InputReMat image, rv::IReWindow* rewindow)
{
    runResult = RunStatus();
    Timer totalTimer;

    try
    {
        if (image.empty())
        {
            throw std::invalid_argument("输入图像为空!");
        }

        //处理
        rv::ReMat dst;
        if (image.channels() == 1)
        {
            dst = image.clone();
        }
        else
        {
            if (isConversion)
            {
                IPreprocess->convertColor(image, dst, code1);
            }
            else
            {
                IPreprocess->extractColorPlane(image, dst, code2);
            }
        }
        runResult.isOk = true;

        //保存参数
        Variant* outputVariant = getOutputSource(outputImage);
        if (outputVariant != nullptr)
        {
            outputVariant->setValue(dst);
        }

        //设置显示图像
        if (rewindow != nullptr)
        {
            rewindow->dispImage(dst);
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
