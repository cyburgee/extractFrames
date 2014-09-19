//
//  main.cpp
//  extractFrames
//
//  Created by Collin Burger on 8/25/14.
//  Copyright (c) 2014 Collin Burger. All rights reserved.
//

#include "main.h"

namespace fs = boost::filesystem;
namespace po = boost::program_options;

int main(int argc, const char * argv[]) {
    
    
    
    string filePrefix;
    string inputFile;
    int startIdx;
    int endIdx;
    //int fps;
    //ofstream progress;
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "produce help message")
    ("input,i",po::value<string>(&inputFile), "path and filename of desired input video")
    ("output,o", po::value<string>(&filePrefix), "prefix of outputfile")
    ("start,s", po::value<int>(&startIdx), "starting frame index")
    ("end,e", po::value<int>(&endIdx), "ending frame index")
    //("fps,f", po::value<int>(&fps), "framerate of video")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    
    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    
    if (vm.count("input")) {
        //cout << "Input file: " << vm["input"].as<std::string>() << ".\n";
    } else {
        cout << "Input file was not set.\n";
        return -1;
    }
    
    if (vm.count("output")) {
        //cout << "Output file: " << vm["output"].as<std::string>() << ".\n";
    } else {
        cout << "Output file was not set.\n";
        return -1;
    }
    
    if (vm.count("start")) {
        //cout << "Starting index:" << vm["start"].as<int>() << ".\n";
        //progress.open(fileProgressString,ofstream::out);
    } else {
        cout << "Starting index was not set.\n";
        return -1;
    }
    if (vm.count("end")) {
        //cout << "Ending index:" << vm["end"].as<int>() << ".\n";
    } else {
        cout << "Ending index was not set.\n";
        return -1;
    }
    /*if(vm.count("fps")){
        cout << "FPS: " << vm["fps"].as<int>() << ".\n";
    }else {
        cout << "FPS wasn't set.\n";
        return -1;
    }*/
    
    
    /*vid.open(inputFile);
    double fps = vid.get(CV_CAP_PROP_FPS);
    //cout << "fps: " << fps << endl;
    //"ffmpeg -ss 589.32 -i 160 Greatest Arnold Schwarzenegger Quotes.mp4 -frames:v 25 loop_%02d.jpg"
    double timeStep = 1/fps;
    double inTime = timeStep*startIdx;
    double outTime = timeStep*endIdx;
    cout << "in Time: " << inTime << endl;
    cout << "out Time: " << outTime << endl;
    string ffmpeg = "ffmpeg -ss ";
    int fileIdx = 0;
    //system("echo $PATH");
    for (double i = inTime; i <= outTime; i+= timeStep ){
        stringstream commandStream;
        commandStream << ffmpeg << i << " -i \"" << inputFile << "\" -frames:v 1 \"" << filePrefix << fileIdx << ".jpg\" -v 0 -y";
        cout << "command: " << commandStream.str() << endl;
        system(commandStream.str().c_str());
        fileIdx++;
    }*/
    vid.open(inputFile);
    //double numFrames = vid.get(CV_CAP_PROP_FRAME_COUNT);
    //double fps = vid.get(CV_CAP_PROP_FPS);
    //cout << "num frames: " << numFrames << endl;
    //cout << "fps: " << fps << endl;
    
    /*Mat trash;
    for(int i = 0; i < startIdx; i++){
        vid.read(trash);
    }*/
    //cvSetCaptureProperty(vid, CV_CAP_PROP_POS_FRAMES, (double)startIdx);
    //vector<int> compression_params;
    //compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    //compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    //compression_params.push_back(1);
    vid.set(CV_CAP_PROP_POS_FRAMES, (double)startIdx);
    
    double dWidth = vid.get(CV_CAP_PROP_FRAME_WIDTH);
    double dHeight = vid.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    Size frameSize(static_cast<int>(dWidth),static_cast<int>(dHeight));
    cout << vid.get(CV_CAP_PROP_FOURCC) << endl;
    cout << vid.get(CV_CAP_PROP_FPS) << endl;
    writer.open(filePrefix, CV_FOURCC('M', 'J', 'P', 'G'), vid.get(CV_CAP_PROP_FPS), frameSize);
    
    vid.set(CV_CAP_PROP_POS_FRAMES, (double)startIdx);
    for (int i = startIdx; i <= endIdx; i++){
        //stringstream output;
        //output << filePrefix << (i - startIdx) << ".jpg";
        //string outputFile = output.str();
        Mat frame;
        if (!vid.read(frame)){
            cerr << "couldn't get next frame" << endl;
            goto end_read;
        }
        
        if (writer.isOpened()){
            writer.write(frame);
        }
        else {
            cout << "fuckit" << endl;
        }
        //imwrite(outputFile, frame);
    }
    //writer.release();
    
    end_read:

    //writer.release();
    //cout << "released" << endl;
    return 0;
}
