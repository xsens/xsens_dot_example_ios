//
//  XsensDotPlotData.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/6/4.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern double const RAD_TO_DEG;

@interface XsensDotPlotData : NSObject

@property (assign, nonatomic) UInt32 packageCounter;

@property (assign, nonatomic) UInt32 timeStamp;

/*
    The Quaternion data
    Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatW;
@property (assign, nonatomic) float quatX;
@property (assign, nonatomic) float quatY;
@property (assign, nonatomic) float quatZ;

/*
   The Euler data
   This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
*/
@property (assign, nonatomic) double euler0;
@property (assign, nonatomic) double euler1;
@property (assign, nonatomic) double euler2;

/*
   The FreeAcc data
   This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
*/
@property (assign, nonatomic) float freeAccX;
@property (assign, nonatomic) float freeAccY;
@property (assign, nonatomic) float freeAccZ;

/*
   The status , clipCountAcc , clipCountGyr
   This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadInertialHighFidelityWithMag
*/
@property (assign, nonatomic) UInt16 status;
@property (assign, nonatomic) UInt8 clipCountAcc;
@property (assign, nonatomic) UInt8 clipCountGyr;

/*
   The iQ data
   This data is invalid in current sdk version
*/
@property (assign, nonatomic) SInt32 iQ0;
@property (assign, nonatomic) SInt32 iQ1;
@property (assign, nonatomic) SInt32 iQ2;

/*
   The iV data
   This data is invalid in current sdk version
*/
@property (assign, nonatomic) SInt32 iV0;
@property (assign, nonatomic) SInt32 iV1;
@property (assign, nonatomic) SInt32 iV2;

/*
   The dQ data
   This data is invalid in current sdk version
*/
@property (assign, nonatomic) double dQ0;
@property (assign, nonatomic) double dQ1;
@property (assign, nonatomic) double dQ2;
@property (assign, nonatomic) double dQ3;

/*
   The dV data
   This data is invalid in current sdk version
*/
@property (assign, nonatomic) double dV0;
@property (assign, nonatomic) double dV1;
@property (assign, nonatomic) double dV2;

/*
   The Acceleration data(m/s2)
   Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadInertialHighFidelityWithMag.
*/
@property (assign, nonatomic) double acc0;
@property (assign, nonatomic) double acc1;
@property (assign, nonatomic) double acc2;

/*
   The Angular velocity data(dps)
   Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadInertialHighFidelityWithMag.
*/
@property (assign, nonatomic) double gyr0;
@property (assign, nonatomic) double gyr1;
@property (assign, nonatomic) double gyr2;

/*
   The Magnetic field data(a.u.)
   Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadInertialHighFidelityWithMag.
*/
@property (assign, nonatomic) double mag0;
@property (assign, nonatomic) double mag1;
@property (assign, nonatomic) double mag2;

/*
    Only support firmware v1.0.0 - MFM mode enable
 */
@property (assign, nonatomic) BOOL mfmEnable;

/*
   The MFM output data
*/
@property (strong, nonatomic) NSData *mtbData;

/*
    Only support firmware v1.0.0 - MFM mode
 */
- (instancetype)initWithPlotDataDefault:(NSData *)data frameNumber:(UInt32)prevTimestamp dataProcessor:(nonnull void *)dataProcessor mfmEnable:(BOOL)mfmEnable;

/*
    Only support firmware v1.0.0 - Match initWithPayloadInertialHighFidelity
*/
- (instancetype)initWithPlotDataInertial:(NSData *)sourceData frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/*
    Only support firmware v1.0.0 - Match initWithPayloadExtendQuternion
*/
- (instancetype)initWithPlotDataOrientation:(NSData *)sourceData;

/*
    This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCompleteQuaternion
 */
- (instancetype)initWithPayloadCompleteQuaternion:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadOrientationEuler
*/
- (instancetype)initWithPayloadQrientationEuler:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadOrientationQuaternion
*/
- (instancetype)initWithPayloadQrientationQuaternion:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadFreeAcceleration
*/
- (instancetype)initWithPayloadFreeAcceleration:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCompleteEuler
*/
- (instancetype)initWithPayloadCompleteEuler:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion
*/
- (instancetype)initWithPayloadExtendQuternion:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadInertialHighFidelityWithMag
*/
- (instancetype)initWithPayloadInertialHighFidelity:(NSData *)data frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadHighFidelityNoMag
*/
- (instancetype)initWithPayloadHighFidelityNoMag:(NSData *)data frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadDeltaQuantitiesWithMag
*/
- (instancetype)initWithPayloadDeltaQuantitiesWithMag:(NSData *)data dataProcessor:(nonnull void *)dataProcessor;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadDeltaQuantitiesNoMag
*/
- (instancetype)initWithPayloadDeltaQuantitiesNoMag:(NSData *)data dataProcessor:(nonnull void *)dataProcessor;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadRateQuantitiesWithMag
*/
- (instancetype)initWithPayloadRateQuantitiesWithMag:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadRateQuantitiesNoMag
*/
- (instancetype)initWithPayloadRateQuantitiesNoMag:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadMFM
*/
- (instancetype)initWithPlotDataMFM:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadExtendedEuler
*/
- (instancetype)initWithPlotDataExtendedEuler:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode1
*/
- (instancetype)initWithPlotDataCustomMode1:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode2
*/
- (instancetype)initWithPlotDataCustomMode2:(NSData *)data;

/*
   This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode3
*/
- (instancetype)initWithPlotDataCustomMode3:(NSData *)data;

/*
    This method called after XsensDotDevice call startExportFileData.
 */
- (instancetype)initWithRecordingData:(NSData *)data selectedData:(NSData *)selectedData frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;;

@end

NS_ASSUME_NONNULL_END
