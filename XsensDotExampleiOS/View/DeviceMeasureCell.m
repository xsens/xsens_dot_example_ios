//
//  DeviceMeasureCell.m
//  XsensDotExampleiOS
//
//  Created by Jayson on 2020/8/26.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import "DeviceMeasureCell.h"
#import "UIViewCategory.h"

@interface DeviceMeasureCell ()

@property (strong, nonatomic) UILabel *nameLabel;
@property (strong, nonatomic) UILabel *orientationLabel;
@property (strong, nonatomic) UILabel *freeAccLabel;

@end

@implementation DeviceMeasureCell

- (void)awakeFromNib
{
    [super awakeFromNib];
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    if(self = [super initWithStyle:style reuseIdentifier:reuseIdentifier])
    {
        [self setupViews];
    }
    return self;
}

- (void)setupViews
{
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    
    UILabel *nameTitle = [[UILabel alloc]initWithFrame:CGRectMake(10, 10, 60, 20)];
    nameTitle.text = @"Name:";
    nameTitle.font = [UIFont systemFontOfSize:14.f];
    
    UILabel *nameLabel = [[UILabel alloc]initWithFrame:CGRectMake(nameTitle.right, 10, 200, 20)];
    nameLabel.textColor = [UIColor grayColor];
    nameLabel.font = [UIFont systemFontOfSize:14.f];
    nameLabel.text = @"Xsens DOT";
    
    UILabel *orientationTitle = [[UILabel alloc]initWithFrame:CGRectMake(10, nameLabel.bottom + 5, 200, 20)];
    orientationTitle.font = [UIFont systemFontOfSize:14.f];
    orientationTitle.text = @"Orientation(deg):";
    
    UILabel *orientationLabel = [[UILabel alloc]initWithFrame:CGRectMake(50, orientationTitle.bottom, 300, 20)];
    orientationLabel.font = [UIFont systemFontOfSize:14.f];
    orientationLabel.textColor = [UIColor grayColor];
    orientationLabel.text = @"-, -, -";
    
    UILabel *freeAccTitle = [[UILabel alloc]initWithFrame:CGRectMake(10, orientationLabel.bottom + 5, 200, 20)];
    freeAccTitle.font = [UIFont systemFontOfSize:14.f];
    freeAccTitle.text = @"Free Acceleration(m/s2):";
    
    UILabel *freeAccLabel = [[UILabel alloc]initWithFrame:CGRectMake(50, freeAccTitle.bottom, 300, 20)];
    freeAccLabel.font = [UIFont systemFontOfSize:14.f];
    freeAccLabel.textColor = [UIColor grayColor];
    freeAccLabel.text = @"-, -, -";
    
    [self.contentView addSubview:nameTitle];
    [self.contentView addSubview:nameLabel];
    [self.contentView addSubview:orientationTitle];
    [self.contentView addSubview:orientationLabel];
    [self.contentView addSubview:freeAccTitle];
    [self.contentView addSubview:freeAccLabel];
    
    self.nameLabel = nameLabel;
    self.orientationLabel = orientationLabel;
    self.freeAccLabel = freeAccLabel;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];
}

- (void)setDevice:(XsensDotDevice *)device
{
    __weak __typeof(self) wself  = self;
    
    _device = device;
    [device setDidParsePlotDataBlock:^(XsensDotPlotData * _Nonnull plotData) {
        [wself refreshData:plotData];
    }];
}

- (void)refreshData:(XsensDotPlotData *)plotData
{
    self.orientationLabel.text = [NSString stringWithFormat:@"%f, %f, %f", plotData.euler0, plotData.euler1, plotData.euler2];
    self.freeAccLabel.text = [NSString stringWithFormat:@" %f, %f, %f", plotData.freeAccX, plotData.freeAccY, plotData.freeAccZ];
}


+ (NSString *)cellIdentifier
{
    return @"DeviceMeasureCell";
}

+ (CGFloat)cellHeight
{
    return 130;
}

@end
