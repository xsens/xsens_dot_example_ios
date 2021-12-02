//
//  DeviceMfmCell.m
//  Xsens DOT
//
//  Created by admin on 2020/9/15.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import "DeviceMfmCell.h"

@interface DeviceMfmCell ()

@property (strong, nonatomic) UILabel *nameLabel;
@property (strong, nonatomic) UILabel *addressLabel;
@property (strong, nonatomic) UIProgressView *progressView;

@property (strong, nonatomic) UILabel *progressLabel;
@property (strong, nonatomic) UILabel *statusLabel;
@property (strong, nonatomic) UIActivityIndicatorView *processingIndicatorView;
@property (strong, nonatomic) UIImageView *finishImageView;
@property (strong, nonatomic) UIButton *reWriteButton;
@property (assign, nonatomic) BOOL disconnectedFlag;
@property (assign, nonatomic) int progress;

@end

@implementation DeviceMfmCell

- (void)awakeFromNib
{
    [super awakeFromNib];
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    if(self = [super initWithStyle:style reuseIdentifier:reuseIdentifier])
    {
        [self localInfoSetup];
        [self subViewsSetup];
    }
    return self;
}

- (void)localInfoSetup
{
    _disconnectedFlag = NO;
    _progress = 0;
}

- (void)subViewsSetup
{
    self.backgroundColor = UIColorClear;
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    
    CGFloat horizontalEdge = 16;
    CGFloat verticalEdge = 12;
    
    UILabel *nameLabel = [[UILabel alloc]initWithFrame:CGRectMake(horizontalEdge, verticalEdge, 200, 20)];
    nameLabel.font = [UIFont xsSemiBoldFont:16.f];
    nameLabel.textColor = UIColorWhite;
    self.nameLabel = nameLabel;
    
    
    UILabel *addressLabel = [[UILabel alloc]initWithFrame:CGRectMake(horizontalEdge, nameLabel.bottom + 5, 200, 20)];
    addressLabel.font = [UIFont xsRegularFont:14.f];
    addressLabel.textColor = UIColorLightGray;
    self.addressLabel = addressLabel;
    
    UILabel *progressLabel = [[UILabel alloc]initWithFrame:CGRectMake(SCREEN_WIDTH - horizontalEdge - 40, nameLabel.bottom, 40, 20)];
    progressLabel.textAlignment = NSTextAlignmentRight;
    progressLabel.textColor = UIColorWhite;
    progressLabel.font = [UIFont xsRegularFont:14.f];
    progressLabel.text = @"0%";
    progressLabel.hidden = YES;
    self.progressLabel = progressLabel;
    
    UILabel *statusLabel = [[UILabel alloc]initWithFrame:CGRectMake(SCREEN_WIDTH - horizontalEdge - 100, nameLabel.bottom, 100, 20)];
    statusLabel.textColor = UIColorWhite;
    statusLabel.font = [UIFont xsRegularFont:14.f];
    statusLabel.text = @"Processing";
    statusLabel.hidden = YES;
    self.statusLabel = statusLabel;
    
    UIActivityIndicatorView *processingIndicatorView = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhite];
    processingIndicatorView.frame = CGRectMake(0, 0, 20, 20);
    processingIndicatorView.origin = CGPointMake(SCREEN_WIDTH - horizontalEdge - 20, nameLabel.bottom);
    processingIndicatorView.hidden = YES;
    self.processingIndicatorView = processingIndicatorView;
    
    UIImageView *finishImageView = [[UIImageView alloc]initWithFrame:CGRectMake(SCREEN_WIDTH - horizontalEdge - 20, nameLabel.bottom, 20, 20)];
    finishImageView.image = [UIImage imageNamed:@"ic_done"];
    finishImageView.hidden = YES;
    self.finishImageView = finishImageView;
    
    UIButton *reWriteButton = [UIButton buttonWithType:UIButtonTypeSystem];
    reWriteButton.frame = CGRectMake(SCREEN_WIDTH - horizontalEdge - 60, nameLabel.bottom, 60, 20);
    
    NSMutableAttributedString *title = [[NSMutableAttributedString alloc] initWithString:@"Rewrite"];
    NSRange titleRange = {0,[title length]};
    [title addAttribute:NSUnderlineStyleAttributeName value:[NSNumber numberWithInteger:NSUnderlineStyleSingle] range:titleRange];
    [reWriteButton setAttributedTitle:title forState:UIControlStateNormal];
    reWriteButton.tintColor = UIColorRed;
    reWriteButton.hidden = YES;
    self.reWriteButton = reWriteButton;
    
    
    UIProgressView *progressView = [[UIProgressView alloc]initWithFrame:CGRectMake(horizontalEdge, addressLabel.bottom + 5, SCREEN_WIDTH - 2 * horizontalEdge, 10)];
    progressView.progressViewStyle = UIProgressViewStyleBar;
    progressView.progressTintColor = nCommonOrangeColor;
    progressView.trackTintColor = UIColorWhite;
    progressView.progress = 0.f;
    progressView.transform = CGAffineTransformMakeScale(1.f, 3.f);
    self.progressView = progressView;
    
    [self.contentView addSubview:nameLabel];
    [self.contentView addSubview:addressLabel];
    [self.contentView addSubview:progressLabel];
    [self.contentView addSubview:statusLabel];
    [self.contentView addSubview:progressView];
    [self.contentView addSubview:finishImageView];
    [self.contentView addSubview:processingIndicatorView];
    [self.contentView addSubview:reWriteButton];
    
//    [self cellStopped];
}

- (void)setDevice:(XsensDotDevice *)device
{
    _device = device;
    self.nameLabel.text = self.device.displayName;
    self.addressLabel.text = self.device.macAddress;
}

#pragma mark - UI

- (void)cellInProgress:(int)progress
{
    if (progress < _progress)
    {
        return;
    }
    _progress = progress;
    self.progressLabel.hidden = NO;
    self.statusLabel.hidden = YES;
    self.finishImageView.hidden = YES;
    self.progressLabel.text = [NSString stringWithFormat:@"%d%@", progress, @"%"];
    self.progressView.progress = (float)progress / 100.f;
    [self.processingIndicatorView stopAnimating];
    self.processingIndicatorView.hidden = YES;
    if (progress == 100)
    {
        [self cellInProcessing];
    }
}

- (void)cellInProcessing
{
    self.progressLabel.hidden = YES;
    self.statusLabel.hidden = NO;
    self.statusLabel.textColor = UIColorWhite;
    self.statusLabel.text = @"Processing";
    self.finishImageView.hidden = YES;
    self.processingIndicatorView.hidden = NO;
    [self.processingIndicatorView startAnimating];
}

- (void)cellWriteToSensor
{
    [self.processingIndicatorView stopAnimating];
    self.processingIndicatorView.hidden = YES;
    self.statusLabel.hidden = NO;
    self.statusLabel.text = @"Write to sensor...";
}

- (void)cellFinished
{
    if (!self.disconnectedFlag)
    {
        self.statusLabel.hidden = NO;
        self.progressLabel.hidden = YES;
        self.statusLabel.text = @"Finished";
        self.statusLabel.textColor = UIColorHex(0x66cc66);
        self.processingIndicatorView.hidden = YES;
        self.finishImageView.hidden = NO;
        self.progress = 0;
    }
}

- (void)cellWriteFailed
{
    self.statusLabel.hidden = NO;
    self.reWriteButton.hidden = NO;
    self.statusLabel.textColor = UIColorRed;
    self.statusLabel.text = @"Write failed.";
}

- (void)cellFailed
{
    self.statusLabel.hidden = NO;
    self.progressLabel.hidden = YES;
    self.statusLabel.textColor = UIColorRed;
    [self.processingIndicatorView stopAnimating];
    self.processingIndicatorView.hidden = YES;
    self.statusLabel.text = @"MFM failed";
}

- (void)cellDisconnected
{
    self.disconnectedFlag = YES;
    self.statusLabel.hidden = NO;
    self.progressLabel.hidden = YES;
    self.statusLabel.textColor = UIColorRed;
    self.processingIndicatorView.hidden = YES;
    self.finishImageView.hidden = YES;
    self.statusLabel.text = @"Disconnected";
    self.progress = 0;
}

- (void)cellStopped
{
    self.statusLabel.hidden = NO;
    self.progressLabel.hidden = YES;
    self.progressView.progress = 0;
    self.statusLabel.textColor = UIColorWhite;
    self.statusLabel.text = @"Stopped";
}

#pragma mark - Class Interface

+ (NSString *)cellIdentifier
{
    return @"DeviceRecordingCell";
}

+ (CGFloat)cellHeight
{
    return 80;
}


@end
