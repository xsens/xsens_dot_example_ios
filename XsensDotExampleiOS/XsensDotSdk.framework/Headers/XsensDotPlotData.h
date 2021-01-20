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

/**
 *  XsensDotData contains all the measurement data. When set setPlotMeasureEnable to YES,
 *  the block will get the data from setDidParsePlotDataBlock. 
 */
@interface XsensDotPlotData : NSObject

/**
 *  @brief The plotting data package counter
 */
@property (assign, nonatomic) UInt32 packageCounter;

/**
 *  @brief The timeStamp
 */
@property (assign, nonatomic) UInt32 timeStamp;

/**
 *  @brief The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatW;
/**
 *  @brief The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatX;
/**
 *  @brief The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatY;
/**
 *  @brief The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatZ;


/**
 *  @brief The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler0;
/**
 *  @brief The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler1;
/**
 *  @brief The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler2;


/**
 *  @brief The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccX;
/**
 *  @brief The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccY;
/**
 *  @brief The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccZ;


/**
 *  @brief The snapshot status of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt16 status;
/**
 *  @brief The clip count of acceleration of the packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt8 clipCountAcc;
/**
 *  @brief The clip count of gyro of the packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt8 clipCountGyr;


/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ0;
/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ1;
/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ2;


/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV0;
/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV1;
/**
 *  @brief The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV2;


/**
 *  @brief The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ0;
/**
 *  @brief The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ1;
/**
 *  @brief The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ2;
/**
 *  @brief The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ3;


/**
 *  @brief The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV0;
/**
 *  @brief The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV1;
/**
 *  @brief The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV2;


/**
 *  @brief The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc0;
/**
 *  @brief The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc1;
/**
 *  @brief The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc2;


/**
 *  @brief The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr0;
/**
 *  @brief The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr1;
/**
 *  @brief The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr2;


/**
 *  @brief The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag0;
/**
 *  @brief The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag1;
/**
 *  @brief The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag2;


/**
 *  @brief The MFM enable ,only support firmware v1.0.0 - MFM mode enable
 */
@property (assign, nonatomic) BOOL mfmEnable;


/**
 *  @brief The MFM output data
 */
@property (strong, nonatomic) NSData *mtbData;

/**
 *  @brief Constructor method , Only support firmware v1.0.0 - MFM mode
 *  @param data The BLE data
 *  @param frameNumber The frame number
 *  @param dataProcessor The DataProcessor object
 *  @param mfmEnable MFM enable
 */
- (instancetype)initWithPlotDataDefault:(NSData *)data frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor mfmEnable:(BOOL)mfmEnable;

/**
 *  @brief Constructor method , Only support firmware v1.0.0 - Match initWithPayloadInertialHighFidelity
 *  @param sourceData The BLE data
 *  @param frameNumber The frame number
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithPlotDataInertial:(NSData *)sourceData frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/**
 *  @brief Constructor method , Only support firmware v1.0.0 - Match initWithPayloadExtendQuternion
 *  @param sourceData The BLE data
 */
- (instancetype)initWithPlotDataOrientation:(NSData *)sourceData;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCompleteQuaternion
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadCompleteQuaternion:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadOrientationEuler
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadQrientationEuler:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadOrientationQuaternion
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadQrientationQuaternion:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadFreeAcceleration
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadFreeAcceleration:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCompleteEuler
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadCompleteEuler:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadExtendQuternion:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadInertialHighFidelityWithMag
 *  @param data The BLE data
 *  @param frameNumber The frame number
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithPayloadInertialHighFidelity:(NSData *)data frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadHighFidelityNoMag
 *  @param data The BLE data
 *  @param frameNumber The frame number
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithPayloadHighFidelityNoMag:(NSData *)data frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadDeltaQuantitiesWithMag
 *  @param data The BLE data
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithPayloadDeltaQuantitiesWithMag:(NSData *)data dataProcessor:(nonnull void *)dataProcessor;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadDeltaQuantitiesNoMag
 *  @param data The BLE data
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithPayloadDeltaQuantitiesNoMag:(NSData *)data dataProcessor:(nonnull void *)dataProcessor;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadRateQuantitiesWithMag
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadRateQuantitiesWithMag:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadRateQuantitiesNoMag
 *  @param data The BLE data
 */
- (instancetype)initWithPayloadRateQuantitiesNoMag:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadMFM
 *  @param data The BLE data
 */
- (instancetype)initWithPlotDataMFM:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadExtendedEuler
 *  @param data The BLE data
 */
- (instancetype)initWithPlotDataExtendedEuler:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode1
 *  @param data The BLE data
 */
- (instancetype)initWithPlotDataCustomMode1:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode2
 *  @param data The BLE data
 */
- (instancetype)initWithPlotDataCustomMode2:(NSData *)data;

/**
 *  @brief Constructor method , This method only call when XSBleDevicePayloadMode is XSBleDevicePayloadCustomMode3
 *  @param data The BLE data
 */
- (instancetype)initWithPlotDataCustomMode3:(NSData *)data;

/**
 *  @brief Constructor method , This method called after XsensDotDevice call startExportFileData.
 *  @param data The BLE data
 *  @param selectedData The data that you want to export
 *  @param frameNumber The frame number
 *  @param dataProcessor The DataProcessor object
 */
- (instancetype)initWithRecordingData:(NSData *)data selectedData:(NSData *)selectedData frameNumber:(UInt32)frameNumber dataProcessor:(nonnull void *)dataProcessor;;

@end

NS_ASSUME_NONNULL_END
