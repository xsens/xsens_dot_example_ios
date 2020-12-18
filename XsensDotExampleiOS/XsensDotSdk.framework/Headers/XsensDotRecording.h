//
//  XsensDotRecording.h
//  XsensDotSdk
//
//  Created by admin on 2020/7/7.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, XSRecordingStatus)
{
    XSRecordingIsIdle = 0,
    XSRecordingIsRecording,
    XSRecordingIsRecordingStopped,
    XSRecordingIsErasing = 100,
    XSRecordingIsFlashInfo,
};

typedef NS_ENUM(NSUInteger, XSExportStatus)
{
    XSExportIsExportingData = 0,
    XSExportIsStopExportingData
};

typedef NS_ENUM(NSUInteger, XSFlashInfoStatus)
{
    XSFlashInfoIsReady = 0,
    XSFlashInfoIsFull,
    XSFlashInfoIsUninitialized,
};

@interface RecordingFile : NSObject

/// The type is Byte
@property (assign, nonatomic) NSUInteger fileSize;
@property (assign, nonatomic) UInt32 timeStamap;

@end

@interface XsensDotRecording : NSObject

@property (assign, nonatomic) XSFlashInfoStatus flashInfoStatus;
@property (assign, nonatomic) XSRecordingStatus recordingStatus;
@property (copy, nonatomic) void (^updateRecordingStatus)(XSRecordingStatus status);
@property (copy, nonatomic) void (^updateExportingStatus)(XSExportStatus status);

// The start recording date: 4 bytes unit is seconds
@property (assign, nonatomic) UInt32 recordingDate;

/*
    The recording time that you set from : - (void)startRecording:(UInt16)recordingTime;
    2 bytes unit is seconds
 */
@property (assign, nonatomic) UInt16 recordingTime;

/*
    If the sensor is in XSRecordingIsRecording this will be useful
 */

@property (assign, nonatomic) UInt32 remainingTime;
@property (assign, nonatomic) NSUInteger fileIndex;

/*
    The recording files.
 */
@property (strong, nonatomic) NSMutableArray <RecordingFile *> *files;

/*
    The exported file list like [0,1,4] , max is files.count.
 */
@property (strong, nonatomic) NSArray *exportFileList;

/*
    Export file done block.
    index which from exportFileList , if result is YES means all files done and NO means finish one of them.
 */
@property (copy, nonatomic) void (^exportFileDone)(NSUInteger index, BOOL result);

@end

NS_ASSUME_NONNULL_END
