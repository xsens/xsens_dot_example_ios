//
//  OtaViewController.m
//  XsensDotExampleiOS
//
//  Created by admin on 2021/7/7.
//  Copyright © 2021 Xsens. All rights reserved.
//

#import "OtaViewController.h"
#import "UIViewCategory.h"
#import <MBProgressHUD.h>
#import <XsensDotSdk/XsensDotOtaManager.h>


/**
 * This is the demo for one sensor to do the OTA function
 * If you want to do OTA for multiple sensors,
 * please make sure to upgrade in sequence, when the first upgrade succeeds, upgrade the next one, and so on.
 */
@interface OtaViewController ()<XsesnDotOtaManagerDelegate>

@property (strong, nonatomic) UIButton *checkUpdate;
@property (strong, nonatomic) UIButton *checkUpdateAndDownload;
@property (strong, nonatomic) UIButton *startOta;
@property (strong, nonatomic) UILabel *statusLabel;
@property (strong, nonatomic) UILabel *progressLabel;

/// Check if the sensor has udpate
@property (assign, nonatomic) BOOL hasUpdated;
/// Check if the sensor's firmware has been downloaded
@property (assign, nonatomic) BOOL hasDownloaded;
/// Ensure that only one method can be executed at the same time
@property (assign, nonatomic) BOOL isProcessing;

@end

@implementation OtaViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self localInfoSetup];
    [self navigationItemsSetup];
    [self setupViews];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [XsensDotOtaManager setOtaManagerDelegate:self];
}

- (void)localInfoSetup
{
    _hasUpdated = NO;
    _hasDownloaded = NO;
    _isProcessing = NO;
}

- (void)navigationItemsSetup
{
    self.title = @"OTA";
    UINavigationBar *navigationBar = self.navigationController.navigationBar;
    navigationBar.tintColor = [UIColor whiteColor];
}

- (void)setupViews
{
    UIView *baseView = self.view;
    CGFloat edge = 15;
    self.edgesForExtendedLayout = UIRectEdgeNone;
    baseView.backgroundColor = [UIColor whiteColor];
    
    UILabel *nameLabelTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, edge, 120, 20)];
    nameLabelTitle.text = @"Device name:";
    nameLabelTitle.font = [UIFont boldSystemFontOfSize:16.f];
    nameLabelTitle.textColor = [UIColor blackColor];
    
    UILabel *nameLabel = [[UILabel alloc]initWithFrame:CGRectMake(nameLabelTitle.right, edge, 120, 20)];
    nameLabel.font = [UIFont systemFontOfSize:14.f];
    nameLabel.textColor = [UIColor grayColor];
    nameLabel.text = self.device.displayName;
    
    UILabel *addressLabelTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, nameLabelTitle.bottom + 10, 130, 20)];
    addressLabelTitle.text = @"Device Address: ";
    addressLabelTitle.font = [UIFont boldSystemFontOfSize:16.f];
    addressLabelTitle.textColor = [UIColor blackColor];
    
    UILabel *addressLabel = [[UILabel alloc]initWithFrame:CGRectMake(addressLabelTitle.right, nameLabelTitle.bottom + 10, 150, 20)];
    addressLabel.text = self.device.displayAddress;
    addressLabel.font = [UIFont systemFontOfSize:14.f];
    addressLabel.textColor = [UIColor grayColor];
    
    UILabel *fmVersionLabelTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, addressLabelTitle.bottom + 10, 150, 20)];
    fmVersionLabelTitle.text = @"Firmware version: ";
    fmVersionLabelTitle.font = [UIFont boldSystemFontOfSize:16.f];
    fmVersionLabelTitle.textColor = [UIColor blackColor];
    
    UILabel *fmVersionLabel = [[UILabel alloc]initWithFrame:CGRectMake(fmVersionLabelTitle.right, addressLabelTitle.bottom + 10, 150, 20)];
    fmVersionLabel.font = [UIFont systemFontOfSize:14.f];
    fmVersionLabel.textColor = [UIColor grayColor];
    fmVersionLabel.text = self.device.firmwareVersion.description;
    
    
    
    UIButton *checkUpdate = [UIButton buttonWithType:UIButtonTypeSystem];
    checkUpdate.frame = CGRectMake(edge, fmVersionLabelTitle.bottom + 30, 150, 40);
    [checkUpdate setTitle:@"Check Update" forState:UIControlStateNormal];
    [checkUpdate setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    checkUpdate.backgroundColor = UIColor.orangeColor;
    [checkUpdate addTarget:self action:@selector(checkUpdateTapped:) forControlEvents:UIControlEventTouchUpInside];
    self.checkUpdate = checkUpdate;
    
    
    UIButton *checkUpdateAndDownload = [UIButton buttonWithType:UIButtonTypeSystem];
    checkUpdateAndDownload.frame = CGRectMake(edge, checkUpdate.bottom + 20, 250, 40);
    [checkUpdateAndDownload setTitle:@"Check Update And Download" forState:UIControlStateNormal];
    [checkUpdateAndDownload setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    checkUpdateAndDownload.backgroundColor = UIColor.orangeColor;
    [checkUpdateAndDownload addTarget:self action:@selector(checkUpdateAndDownloadTapped:) forControlEvents:UIControlEventTouchUpInside];
    self.checkUpdateAndDownload = checkUpdateAndDownload;
    
    
    UIButton *startOta = [UIButton buttonWithType:UIButtonTypeSystem];
    startOta.frame = CGRectMake(edge, checkUpdateAndDownload.bottom + 20, 100, 40);
    [startOta setTitle:@"Start OTA" forState:UIControlStateNormal];
    [startOta setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    startOta.backgroundColor = UIColor.orangeColor;
    [startOta addTarget:self action:@selector(startOtaTapped:) forControlEvents:UIControlEventTouchUpInside];
    self.startOta = startOta;
    
    
    UILabel *statusLabelTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, startOta.bottom + 30, 120, 20)];
    statusLabelTitle.text = @"Update Status:";
    statusLabelTitle.font = [UIFont boldSystemFontOfSize:16.f];
    statusLabelTitle.textColor = [UIColor blackColor];
    
    UILabel *statusLabel = [[UILabel alloc]initWithFrame:CGRectMake(statusLabelTitle.right, startOta.bottom + 30, 300, 20)];
    statusLabel.font = [UIFont systemFontOfSize:14.f];
    statusLabel.textColor = [UIColor grayColor];
    statusLabel.text = @"-";
    self.statusLabel = statusLabel;
    
    UILabel *progressTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, statusLabelTitle.bottom + 10, 120, 20)];
    progressTitle.text = @"OTA progress:";
    progressTitle.font = [UIFont boldSystemFontOfSize:16.f];
    progressTitle.textColor = [UIColor blackColor];
    
    UILabel *progressLabel = [[UILabel alloc]initWithFrame:CGRectMake(progressTitle.right, statusLabelTitle.bottom + 10, 200, 20)];
    progressLabel.font = [UIFont systemFontOfSize:14.f];
    progressLabel.textColor = [UIColor grayColor];
    progressLabel.text = @"-";
    self.progressLabel = progressLabel;
    
    [baseView addSubview:nameLabelTitle];
    [baseView addSubview:nameLabel];
    [baseView addSubview:addressLabelTitle];
    [baseView addSubview:addressLabel];
    [baseView addSubview:fmVersionLabelTitle];
    [baseView addSubview:fmVersionLabel];
    [baseView addSubview:checkUpdate];
    [baseView addSubview:checkUpdateAndDownload];
    [baseView addSubview:startOta];
    [baseView addSubview:statusLabelTitle];
    [baseView addSubview:statusLabel];
    [baseView addSubview:progressTitle];
    [baseView addSubview:progressLabel];
}

/// Show check and download popup
- (void)showCheckAndDownload
{
    MBProgressHUD *hud =  [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.offset = CGPointMake(0, 200);
    hud.detailsLabel.text = @"Please check update and download first";
    [hud hideAnimated:YES afterDelay:1.0f];
}

/// The current process is being executed
- (void)showProcessing
{
    MBProgressHUD *hud =  [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.offset = CGPointMake(0, 200);
    hud.detailsLabel.text = @"Please wait for current process complete";
    [hud hideAnimated:YES afterDelay:1.0f];
}


#pragma mark -- TouchEvent

/// Check the OTA update
- (void)checkUpdateTapped:(UIButton *)sender
{
    if (!self.isProcessing)
    {
        self.isProcessing = YES;
        [[XsensDotOtaManager defaultManager]checkOtaUpdates:self.device];
    }
    else
    {
        [self showProcessing];
    }
    
}

/// Check the OTA update and download
- (void)checkUpdateAndDownloadTapped:(UIButton *)sender
{
    if (!self.isProcessing)
    {
        self.isProcessing = YES;
        [[XsensDotOtaManager defaultManager]checkOtaUpdatesAndDownload:self.device];
    }
    else
    {
        [self showProcessing];
    }
    
}

/// Start doing the OTA
- (void)startOtaTapped:(UIButton *)sender
{
    if (!self.isProcessing)
    {
        if (self.hasUpdated && self.hasDownloaded)
        {
            self.isProcessing = YES;
            [[XsensDotOtaManager defaultManager]startOta:self.device];
        }
        else
        {
            [self showCheckAndDownload];
        }
    }
    else
    {
        [self showProcessing];
    }
}

#pragma mark -- XsesnDotOtaManagerDelegate

/**
 * When call  checkOtaUpdates or checkOtaUpdatesAndDownload this method will be triggered.
 * @param address The XsensDotDevice mac address
 * @param result The update result
 * @param version The firmeare version
 * @param releaseNotes The firmware release notes
 */
- (void)onOtaUpdates:(NSString *)address result:(BOOL)result version:(NSString *)version releaseNotes:(NSString *)releaseNotes
{
    self.isProcessing = NO;
    
    if (result && ![version isEqualToString:@""])
    {
        self.hasUpdated = YES;
        self.statusLabel.text = [NSString stringWithFormat:@"Has update version is %@", version];
    }
    else
    {
        self.statusLabel.text = @"No update";
    }
}

/**
 * When call checkOtaRollbackAndDownload or checkOtaUpdatesAndDownload and the firmeare has been downloaded ,this method will be triggered.
 * @param address The XsensDotDevice mac address
 * @param version The firmware version
 */
- (void)onOtaDownload:(NSString *)address version:(NSString *)version
{
    self.isProcessing = NO;
    
    if (![version isEqualToString:@""])
    {
        self.hasDownloaded = YES;
        self.statusLabel.text = [NSString stringWithFormat:@"Firmware has downloaded %@", version];
    }
    else
    {
        self.statusLabel.text = @"No firmware download";
    }
}

/**
 * This method will be triggered after call startOta
 * @param address The XsensDotDevice mac address
 * @param result The start result
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaStart:(NSString *)address result:(BOOL)result errorCode:(int)errorCode
{
    if (result)
    {
        self.statusLabel.text = @"Start OTA success";
    }
    else
    {
        self.statusLabel.text = @"Start OTA fail";
    }
}

/**
 * This method will be triggered after call startOta
 * @param address The XsensDotDevice mac address
 * @param progress The progress while doing OTA
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaProgress:(NSString *)address progress:(float)progress errorCode:(int)errorCode
{
    self.progressLabel.text = [NSString stringWithFormat:@"OTA progress: %f", progress];
}

/**
 * This method will be triggered after OTA finished or call stopOta
 * @param address The XsensDotDevice mac address
 * @param result The OTA finished result
 * @param errorCode The error code (0 indicate had no errors)
 */
- (void)onOtaEnd:(NSString *)address result:(BOOL)result errorCode:(int)errorCode
{
    self.isProcessing = NO;
    
    if (result)
    {
        self.statusLabel.text = @"OTA success";
    }
    else
    {
        self.statusLabel.text = @"OTA failed";
    }
}

@end
