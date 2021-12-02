//
//  DeviceConnectCell.m
//  XsensDotDebug
//
//  Created by Jayson on 2020/6/5.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import "DeviceConnectCell.h"
#import <XsensDotSdk/XsensDotDevice.h>

@interface DeviceConnectCell ()

@property (strong, nonatomic) UISwitch *connectButton;
@property (strong, nonatomic) UILabel *tagLabel;
@property (strong, nonatomic) UILabel *addressLabel;
@property (strong, nonatomic) UILabel *batteryLabel;

@end

@implementation DeviceConnectCell

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
    
    UISwitch *connectButton = [[UISwitch alloc]init];
    connectButton.onTintColor = [UIColor orangeColor];
    [connectButton addTarget:self action:@selector(handleConnect:) forControlEvents:UIControlEventTouchUpInside];
    
    UILabel *tagLabel  = [[UILabel alloc]initWithFrame:CGRectMake(16, 20, 100, 20)];
    tagLabel.text = @"Xsens DOT";
    tagLabel.font = [UIFont systemFontOfSize:16.f];
    
    UILabel *addressLabel  = [[UILabel alloc]initWithFrame:CGRectMake(16, tagLabel.bottom + 5, 140, 20)];
    addressLabel.font = [UIFont systemFontOfSize:14.f];
    addressLabel.textColor = [UIColor grayColor];
    
    UILabel *batteryLabel  = [[UILabel alloc]initWithFrame:CGRectMake(addressLabel.right, addressLabel.top, 100, 20)];
    batteryLabel.font = [UIFont systemFontOfSize:14.f];
    batteryLabel.textColor = [UIColor grayColor];
    
    [self.contentView addSubview:tagLabel];
    [self.contentView addSubview:addressLabel];
    [self.contentView addSubview:batteryLabel];
    self.accessoryView = connectButton;
    
    self.tagLabel = tagLabel;
    self.addressLabel = addressLabel;
    self.batteryLabel = batteryLabel;
    self.connectButton = connectButton;
    
}

- (void)handleConnect:(UIButton *)sender
{
    if (self.connectAction != nil)
    {
        self.connectAction(self);
    }
}


- (void)setDevice:(XsensDotDevice *)device
{
    _device = device;
    self.addressLabel.text = device.macAddress;
    self.tagLabel.text = device.displayName;
    [self refreshDeviceStatus];
}

- (void)refreshDeviceStatus
{
    XsensDotDevice *device = self.device;
    switch (device.state) {
        case CBPeripheralStateConnected:
        {
            [self.connectButton setOn:YES];
            self.tagLabel.text = device.displayName;
            if (device.battery.chargeState)
            {
                self.batteryLabel.text = [NSString stringWithFormat:@"%zd%@ Charging" , device.battery.value, @"%"];
            }
            else
            {
                self.batteryLabel.text = [NSString stringWithFormat:@"%zd%@" , device.battery.value, @"%"];
            }
            break;
        }
        case CBPeripheralStateConnecting:
        {
            break;
        }
        case CBPeripheralStateDisconnected:
        {
            [self.connectButton setOn:NO];
            self.batteryLabel.text = @"";
            break;
        }
        default:
            break;
    }
}

+ (NSString *)cellIdentifier
{
    return @"DeviceConnectCell";
}

+ (CGFloat)cellHeight
{
    return 80;
}

@end
