//
//  XsensDotStatisticsInfo.h
//  XsensDotSdk
//
//  Created by Nick Yang on 2019/8/1.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSInteger const BLEStatisticsInfoSourceStandardLength;

@interface XsensDotStatisticsInfo : NSObject

@property (strong, nonatomic) NSData *sourceData;

@property (assign, nonatomic) UInt8 PHY;
@property (assign, nonatomic) UInt16 max_TX_PDU_Length;
@property (assign, nonatomic) UInt16 max_RX_PDU_Length;
@property (assign, nonatomic) UInt16 connectInterval;
@property (assign, nonatomic) UInt16 ATT_MTU;
@property (assign, nonatomic) UInt8 RSSI;
@property (assign, nonatomic) UInt8 channelIndex;
@property (assign, nonatomic) UInt32 plotNumber;
@property (assign, nonatomic) UInt32 plotFirst;
@property (assign, nonatomic) UInt32 plotLast;

+ (instancetype)statisticsInfoWithSourceData:(NSData *)data;
- (NSString *)briefDescription;

@end

NS_ASSUME_NONNULL_END
