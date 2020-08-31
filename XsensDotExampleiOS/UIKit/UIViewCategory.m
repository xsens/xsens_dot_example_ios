//
//  UIViewCategory.m
//  Xsens DOT
//
//  Created by Jayson on 2019/5/8.
//  Copyright © 2019 Xsens. All rights reserved.
//

#import "UIViewCategory.h"

CGFloat const UINavigationBarHeight           = 44;
CGFloat const UIStatusBarHeightCommon         = 20;
CGFloat const UIStatusBarHeightForIPhoneX     = 44;
CGFloat const UIHomeIndicatorHeightForIPhoneX = 34;

#pragma mark - InnerFrameFunction

CGSize CGSizeMaxSpaceSize(CGSize size1, CGSize size2)
{
    return CGSizeMake(MAX(size1.width, size2.width), MAX(size1.height, size2.height));
}

CGRect CGRectMakeFromSize(CGSize size)
{
    return CGRectMake(0, 0, size.width, size.height);
}

CGFloat CGFloatThroughViewScale(CGFloat length)
{
    return length * [UIView viewStandardScale];
}

CGSize CGSizeThroughViewScale(CGSize originalSize)
{
    CGFloat scale = [UIView viewStandardScale];
    return CGSizeMake(originalSize.width * scale, originalSize.height * scale);
}

CGPoint CGPointThroughViewScale(CGPoint originalPoint)
{
    CGFloat scale = [UIView viewStandardScale];
    return CGPointMake(originalPoint.x * scale, originalPoint.y * scale);
}

CGRect CGRectThroughViewScale(CGRect originalFrame)
{
    CGFloat scale = [UIView viewStandardScale];
    return CGRectMake(originalFrame.origin.x * scale, originalFrame.origin.y * scale, originalFrame.size.width * scale, originalFrame.size.height * scale);
}

/*
 ----------------------------------------
 UIView (FrameGeometry)
 ----------------------------------------
 */
@implementation UIView (FrameGeometry)

#pragma mark - FrameOrigin

- (CGPoint)origin
{
    return self.frame.origin;
}

- (void)setOrigin:(CGPoint)aPoint
{
    CGRect newFrame = self.frame;
    newFrame.origin = aPoint;
    self.frame = newFrame;
}

- (CGPoint)bottomLeft
{
    CGFloat x = self.frame.origin.x;
    CGFloat y = self.frame.origin.y + self.frame.size.height;
    return CGPointMake(x, y);
}

- (void)setBottomLeft:(CGPoint)bottomLeft
{
    CGRect frame = self.frame;
    frame.origin.x = bottomLeft.x;
    frame.origin.y = bottomLeft.y - frame.size.height;
    self.frame = frame;
}

- (CGPoint)bottomRight
{
    CGFloat x = self.frame.origin.x + self.frame.size.width;
    CGFloat y = self.frame.origin.y + self.frame.size.height;
    return CGPointMake(x, y);
}

- (void)setBottomRight:(CGPoint)bottomRight
{
    CGRect frame = self.frame;
    frame.origin.x = bottomRight.x - frame.size.width;
    frame.origin.y = bottomRight.y - frame.size.height;
    self.frame = frame;
}

- (CGPoint)topRight
{
    CGFloat x = self.frame.origin.x + self.frame.size.width;
    CGFloat y = self.frame.origin.y;
    return CGPointMake(x, y);
}

- (void)setTopRight:(CGPoint)topRight
{
    CGRect frame = self.frame;
    frame.origin.x = topRight.x - frame.size.width;
    frame.origin.y = topRight.y;
    self.frame = frame;
}

#pragma mark - FrameSize

- (CGSize)size
{
    return self.frame.size;
}

- (void)setSize:(CGSize)aSize
{
    CGRect frame = self.frame;
    frame.size = aSize;
    self.frame = frame;
}

- (CGFloat)height
{
    return self.frame.size.height;
}

- (void)setHeight:(CGFloat)newHeight
{
    CGRect frame = self.frame;
    frame.size.height = newHeight;
    self.frame = frame;
}

- (CGFloat)width
{
    return self.frame.size.width;
}

- (void)setWidth:(CGFloat)newWidth
{
    CGRect frame = self.frame;
    frame.size.width = newWidth;
    self.frame = frame;
}

#pragma mark - Indicator

- (CGPoint)innerCenter
{
    return CGPointMake(self.frame.size.width * 0.5, self.frame.size.height * 0.5);
}

- (CGPoint)boundsCenter
{
    return CGPointMake(self.bounds.size.width * 0.5, self.bounds.size.height * 0.5);
}

- (CGFloat)halfWidth
{
    return self.frame.size.width * 0.5;
}

- (CGFloat)halfHeight
{
    return self.frame.size.height * 0.5;
}

#pragma mark - Edge

- (CGFloat)top
{
    return self.frame.origin.y;
}

- (void)setTop:(CGFloat)newTop
{
    CGRect newFrame = self.frame;
    newFrame.origin.y = newTop;
    self.frame = newFrame;
}

- (CGFloat)left
{
    return self.frame.origin.x;
}

- (void)setLeft:(CGFloat)newLeft
{
    CGRect newFrame = self.frame;
    newFrame.origin.x = newLeft;
    self.frame = newFrame;
}

- (CGFloat)bottom
{
    return self.frame.origin.y + self.frame.size.height;
}

- (void)setBottom:(CGFloat)newBottom
{
    CGRect newFrame = self.frame;
    newFrame.origin.y = newBottom - self.frame.size.height;
    self.frame = newFrame;
}

- (CGFloat)right
{
    return self.frame.origin.x + self.frame.size.width;
}

- (void)setRight:(CGFloat)newRight
{
    CGFloat delta = newRight - (self.frame.origin.x + self.frame.size.width);
    CGRect newFrame = self.frame;
    newFrame.origin.x += delta ;
    self.frame = newFrame;
}

#pragma mark - CenterPoint

- (CGFloat)centerX
{
    return self.center.x;
}

- (void)setCenterX:(CGFloat)centerX
{
    CGPoint center = self.center;
    center.x = centerX;
    self.center = center;
}

- (CGFloat)centerY
{
    return self.center.y;
}

- (void)setCenterY:(CGFloat)centerY
{
    CGPoint center = self.center;
    center.y = centerY;
    self.center = center;
}

#pragma mark - EdgeCenter

- (CGPoint)topEdgeCenter
{
    return CGPointMake(self.center.x, self.frame.origin.y);
}

- (void)setTopEdgeCenter:(CGPoint)topEdgeCenter
{
    self.center = CGPointMake(topEdgeCenter.x, topEdgeCenter.y + self.frame.size.height * 0.5);
}

- (CGPoint)bottomEdgeCenter
{
    return CGPointMake(self.center.x, self.frame.origin.y + self.frame.size.height);
}

- (void)setBottomEdgeCenter:(CGPoint)bottomEdgeCenter
{
    self.center = CGPointMake(bottomEdgeCenter.x, bottomEdgeCenter.y - self.frame.size.height * 0.5);
}

- (CGPoint)leftEdgeCenter
{
    return CGPointMake(self.frame.origin.x, self.center.y);
}

- (void)setLeftEdgeCenter:(CGPoint)leftEdgeCenter
{
    self.center = CGPointMake(leftEdgeCenter.x + self.frame.size.width * 0.5, leftEdgeCenter.y);
}

- (CGPoint)rightEdgeCenter
{
    return CGPointMake(self.frame.origin.x + self.frame.size.width, self.center.y);
}

- (void)setRightEdgeCenter:(CGPoint)rightEdgeCenter
{
    self.center = CGPointMake(rightEdgeCenter.x - self.frame.size.width * 0.5, rightEdgeCenter.y);
}

#pragma mark - FrameTransform

// Scaling
- (void)scaleBy:(CGFloat)scaleFactor
{
    CGRect newFrame = self.frame;
    newFrame.size.width *= scaleFactor;
    newFrame.size.height *= scaleFactor;
    self.frame = newFrame;
}

#pragma mark - ViewScale

+ (CGFloat)viewStandardScale
{
#if 0
    return [self viewStandardScaleBasedOnIPhone6];
#else
    return [self viewStandardScaleBasedOnIPhone5];
#endif
}

+ (CGFloat)viewStandardScaleBasedOnIPhone6
{
    /*
     缩放率
     4 4s           :320x480, 0.85
     5 5s 5c SE     :320x568, 0.85
     6 6s 7 8       :375x667, 1.0
     6+ 6s+ 7+ 8+   :414x736, 1.10
     X XS           :375x812, 1.0
     XR             :414x896, 1.10
     XS Max         :414x896, 1.10
     */
    static CGFloat viewStandardScaleValue = 1.0;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        CGFloat screenWidth = [UIScreen mainScreen].bounds.size.width;
        CGFloat standardWidth = 375;
        NSString *scaleString = [NSString stringWithFormat:@"%.02f", screenWidth / standardWidth];
        viewStandardScaleValue = scaleString.floatValue;
    });
    return viewStandardScaleValue;
}

+ (CGFloat)viewStandardScaleBasedOnIPhone5
{
    /*
     缩放率
     4 4s           :320x480, 1.0
     5 5s 5c SE     :320x568, 1.0
     6 6s 7 8       :375x667, 1.17
     6+ 6s+ 7+ 8+   :414x736, 1.29
     X XS           :375x812, 1.17
     XR             :414x896, 1.29
     XS Max         :414x896, 1.29
     */
    static CGFloat viewStandardScaleValue = 1.0;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        CGFloat screenWidth = [UIScreen mainScreen].bounds.size.width;
        CGFloat standardWidth = 320;
        if(screenWidth > standardWidth)
        {
            NSString *scaleString = [NSString stringWithFormat:@"%.02f", screenWidth / standardWidth];
            viewStandardScaleValue = scaleString.floatValue;
        }
    });
    return viewStandardScaleValue;
}

@end
