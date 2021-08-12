//
//  XsensDotRecording.h
//  XsensDotSdk
//
//  Created by admin on 2020/7/7.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  This class has all the properties of recording, including flashInfoStatus, recordingStatus, recordingdata, recordingTime etc.
 *  XsensDotDevice has a property of recording, you can control it after XsensDotDevice connected.
 */
typedef NS_ENUM(NSUInteger, XSRecordingStatus)
{
    /** * The normal mode and can starting recording  */
    XSRecordingIsIdle = 0,
    /** * In recording  */
    XSRecordingIsRecording,
    /** * The recording stopped  */
    XSRecordingIsRecordingStopped,
    /** * The flash is erasing data  */
    XSRecordingIsErasing = 100,
    /** * The flash is getting flash info  */
    XSRecordingIsFlashInfo,
};

/**
 *  The sensor in exporting recording data status
 */
typedef NS_ENUM(NSUInteger, XSExportStatus)
{
    XSExportIsExportingData = 0,
    XSExportIsStopExportingData
};

/**
 *  The sensor flash info status
 */
typedef NS_ENUM(NSUInteger, XSFlashInfoStatus)
{
    /** * Can start recording */
    XSFlashInfoIsReady = 0,
    /** * The flash storage is full */
    XSFlashInfoIsFull,
    /** * The flash storage is uninitialize , need eraseData first*/
    XSFlashInfoIsUninitialized,
};

/**
 *  The Xsens DOT recording file  type class , it has file size and timestamp
 */
@interface XsensDotRecordingFile : NSObject

/**
 *  The file size unit is Byte
 */
@property (assign, nonatomic) NSUInteger fileSize;

/**
 *  The file timeStamap (create time)
 */
@property (assign, nonatomic) UInt32 timeStamap;

@end

/**
    The Xsens DOT recording control class
 */
@interface XsensDotRecording : NSObject

/**
 *  The sensor flash info status
 */
@property (assign, nonatomic) XSFlashInfoStatus flashInfoStatus;

/**
 *  The current recording status in recording mode
 */
@property (assign, nonatomic) XSRecordingStatus recordingStatus;

/**
 *  The recording status changed block
 */
@property (copy, nonatomic) void (^updateRecordingStatus)(XSRecordingStatus status);

/**
 *  The exporting recording file data changed block
 */
@property (copy, nonatomic) void (^updateExportingStatus)(XSExportStatus status);

/**
 *  The start recording date: 4 bytes unit is seconds
 */
@property (assign, nonatomic) UInt32 recordingDate;

/**
 *  The recording time that you set from : - (void)startRecording:(UInt16)recordingTime, unit is seconds
 */
@property (assign, nonatomic) UInt16 recordingTime;

/**
 *  The remaining time of recording, If the sensor is in XSRecordingIsRecording this will be useful
 */
@property (assign, nonatomic) UInt32 remainingTime;

/**
 *  The current exporting file index
 */
@property (assign, nonatomic) NSUInteger fileIndex;

/**
 *  The recording file list.
 */
@property (strong, nonatomic) NSMutableArray <XsensDotRecordingFile *> *files;

/**
 *  The exporting file index array , list like [0,1,4] , max is files.count.
 */
@property (strong, nonatomic) NSArray *exportFileList;

/**
 *  The exporting file done block, index is from exportFileList , if result is YES means all files done and NO means finish one of them.
 */
@property (copy, nonatomic) void (^exportFileDone)(NSUInteger index, BOOL result);

@end

NS_ASSUME_NONNULL_END
