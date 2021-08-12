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
 *  The plotting data package counter
 */
@property (assign, nonatomic) UInt32 packageCounter;

/**
 *  The timeStamp
 */
@property (assign, nonatomic) UInt32 timeStamp;

/**
 *  The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatW;
/**
 *  The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatX;
/**
 *  The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatY;
/**
 *  The XKF orientation  data of packet as quaternion.
 *  @discussion  Only valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion.
 */
@property (assign, nonatomic) float quatZ;


/**
 *  The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler0;
/**
 *  The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler1;
/**
 *  The Euler data
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) double euler2;


/**
 *  The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccX;
/**
 *  The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccY;
/**
 *  The free acceleration data of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is XSBleDevicePayloadExtendedQuaternion or XSBleDevicePayloadCompleteEuler
 */
@property (assign, nonatomic) float freeAccZ;


/**
 *  The snapshot status of packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt16 status;
/**
 *  The clip count of acceleration of the packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt8 clipCountAcc;
/**
 *  The clip count of gyro of the packet.
 *  @discussion This data is valid if the XSBleDevicePayloadMode is: XSBleDevicePayloadExtendedEuler, XSBleDevicePayloadExtendedQuaternion
 *              XSBleDevicePayloadInertialHighFidelityWithMag, XSBleDevicePayloadHighFidelityNoMag
 */
@property (assign, nonatomic) UInt8 clipCountGyr;


/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ0;
/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ1;
/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iQ2;


/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV0;
/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV1;
/**
 *  The Xsens Proprietary Data format.
 */
@property (assign, nonatomic) SInt32 iV2;


/**
 *  The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ0;
/**
 *  The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ1;
/**
 *  The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ2;
/**
 *  The output orientation increment data array after data processing.
 */
@property (assign, nonatomic) double dQ3;


/**
 *  The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV0;
/**
 *  The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV1;
/**
 *  The output velocity increment data array after data processing.
 */
@property (assign, nonatomic) double dV2;


/**
 *  The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc0;
/**
 *  The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc1;
/**
 *  The acceleration data of packet, the unit is m/s2.
 */
@property (assign, nonatomic) double acc2;


/**
 *  The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr0;
/**
 *  The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr1;
/**
 *  The gyro data of packet, the unit is RPS.
 */
@property (assign, nonatomic) double gyr2;


/**
 *  The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag0;
/**
 *  The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag1;
/**
 *  The mag data of packet, the unit is uT.
 */
@property (assign, nonatomic) double mag2;


/**
 *  The MFM enable ,only support firmware v1.0.0 - MFM mode enable
 */
@property (assign, nonatomic) BOOL mfmEnable;


/**
 *  The MFM output data
 */
@property (strong, nonatomic) NSData *mtbData;

/**
 *  Calculating freeAcc for custom mode 4, default local gravity is 9.8127
 *  @discussion To get correct freeAcc , the quaternion and acc data must be effective . The length of the array is 3
 */
- (double *)getCalFreeAcc;

/**
 *  Calculating freeAcc for custom mode 4
 *  @param localGravity Set the custom gravity
 *  @discussion To get correct freeAcc , the quaternion and acc data must be effective. The length of the array is 3
 */
- (double *)getCalFreeAcc:(double)localGravity;

@end

NS_ASSUME_NONNULL_END
