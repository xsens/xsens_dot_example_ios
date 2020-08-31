//
//  XsensDotUpdatePacket.h
//  XsensDotSdk
//
//  Created by Jayson on 2020/3/24.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XsensDotUpdatePacket : NSObject

@property (assign, nonatomic) UInt8 preamble;
@property (assign, nonatomic) UInt8 typeResult;
@property (assign, nonatomic) UInt8 typePacket;
@property (assign, nonatomic) UInt8 typeError;

@property (strong, nonatomic) NSString *deviceAddress;
@property (assign, nonatomic) BOOL success;

+ (instancetype)initWithDFUStatus:(NSData *)data;

@end

NS_ASSUME_NONNULL_END
