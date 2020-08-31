//
//  UIViewCategory.h
//  Xsens DOT
//
//  Created by Jayson on 2019/5/8.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QuartzCore/QuartzCore.h"

typedef NS_ENUM(NSUInteger, UIViewAutoresizingAdditional) {
    UIViewAutoresizingFlexibleHorizontalMargin  = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin,
    UIViewAutoresizingFlexibleVerticalMargin    = UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleBottomMargin,
    UIViewAutoresizingFlexibleAllAround         = UIViewAutoresizingFlexibleHorizontalMargin | UIViewAutoresizingFlexibleVerticalMargin,
    UIViewAutoresizingFlexibleSize              = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight,
};

extern CGFloat const UINavigationBarHeight;
extern CGFloat const UIStatusBarHeightCommon;
extern CGFloat const UIStatusBarHeightForIPhoneX;
extern CGFloat const UIHomeIndicatorHeightForIPhoneX;

extern CGSize CGSizeMaxSpaceSize(CGSize size1, CGSize size2);
extern CGRect CGRectMakeFromSize(CGSize size);
extern CGFloat CGFloatThroughViewScale(CGFloat length);
extern CGSize CGSizeThroughViewScale(CGSize originalSize);
extern CGPoint CGPointThroughViewScale(CGPoint originalPoint);
extern CGRect CGRectThroughViewScale(CGRect originalFrame);

NS_ASSUME_NONNULL_BEGIN

@interface UIView (FrameGeometry)

@property CGPoint origin;
@property CGPoint bottomLeft;
@property CGPoint bottomRight;
@property CGPoint topRight;

@property CGSize size;
@property CGFloat height;
@property CGFloat width;
@property (readonly) CGPoint innerCenter;
@property (readonly) CGPoint boundsCenter;
@property (readonly) CGFloat halfHeight;
@property (readonly) CGFloat halfWidth;

@property CGFloat top;
@property CGFloat left;
@property CGFloat bottom;
@property CGFloat right;
@property CGFloat centerX;
@property CGFloat centerY;

@property CGPoint topEdgeCenter;
@property CGPoint bottomEdgeCenter;
@property CGPoint leftEdgeCenter;
@property CGPoint rightEdgeCenter;

- (void)scaleBy:(CGFloat)scaleFactor;
+ (CGFloat)viewStandardScale;

@end

NS_ASSUME_NONNULL_END
