//
//  MeasureViewController.m
//  XsensDotExampleiOS
//
//  Created by Jayson on 2020/8/26.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import "MeasureViewController.h"
#import "DeviceMeasureCell.h"
#import <XsensDotSdk/XsensDotSyncManager.h>
#import <XsensDotSdk/XsensDotDefine.h>
#import <MBProgressHUD.h>

@interface MeasureViewController ()<UITableViewDelegate,UITableViewDataSource>

@property (strong, nonatomic) UILabel *modeLabel;
@property (strong, nonatomic) UILabel *pathLabel;
@property (strong, nonatomic) UIButton *startButton;
@property (assign, nonatomic) UILabel *syncStatusLabel;
@property (assign, nonatomic) UILabel *logFilePathLabel;
@property (strong, nonatomic) UITableView *tableView;
/// the progress hud of syncing.
@property (assign, nonatomic) MBProgressHUD *syncingHud;
/// Check the measureing is started
@property (assign, nonatomic) BOOL startFlag;
/// Enable the  log file in sdk.
/// Log file path:  Log file(s) stored in: \n Files -> On My iPhone -> YourApp -> Logs
@property (assign, nonatomic) BOOL logEnable;
/// the result of synchronization
@property (assign, nonatomic) BOOL syncResult;
/// the sync flag(enable or disable sync)
@property (assign, nonatomic) BOOL syncEnable;

@end

@implementation MeasureViewController

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
    // Add notification
    [self addObserver];
}


- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    // Remove notification
    [self removeObserver];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    if (self.startFlag)
    {
        [self stopMeasure];
    }
}

- (void)localInfoSetup
{
    _syncResult = YES;
    _logEnable = NO;
    _syncEnable = NO;
}

- (void)navigationItemsSetup
{
    self.title = @"Measure";
    UINavigationBar *navigationBar = self.navigationController.navigationBar;
    navigationBar.tintColor = [UIColor whiteColor];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:self.startButton];
}

- (UIButton *)startButton
{
    if (_startButton == nil)
    {
        _startButton = [UIButton buttonWithType:UIButtonTypeSystem];
        [_startButton setTitle:@"START" forState:UIControlStateNormal];
        [_startButton setTintColor:[UIColor whiteColor]];
        _startButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightBold];
        [_startButton addTarget:self action:@selector(handleStartButton:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _startButton;
}

- (void)setupViews
{
    UIView *baseView = self.view;
    CGFloat edge = 15;
    self.edgesForExtendedLayout = UIRectEdgeNone;
    baseView.backgroundColor = [UIColor whiteColor];
    
    UILabel *label = [[UILabel alloc]initWithFrame:CGRectMake(edge, edge, 60, 20)];
    label.text = @"Mode:";
    label.font = [UIFont boldSystemFontOfSize:16.f];
    label.textColor = [UIColor blackColor];
    
    UILabel *modeLabel = [[UILabel alloc]initWithFrame:CGRectMake(label.right, edge, 120, 20)];
    modeLabel.text = @"Complete(Euler)";
    modeLabel.font = [UIFont systemFontOfSize:14.f];
    modeLabel.textColor = [UIColor grayColor];
    
    UILabel *logLabel = [[UILabel alloc]initWithFrame:CGRectMake(modeLabel.right + 50, edge, 50, 20)];
    logLabel.text = @"Log:";
    
    UISwitch *logSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(logLabel.right, edge - 5, 50, 30)];
    [logSwitch addTarget:self action:@selector(handleLogSwitch:) forControlEvents:UIControlEventTouchUpInside];
    
    UILabel *syncStatusTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, logLabel.bottom + 10, 100, 20)];
    syncStatusTitle.text = @"Sync status: ";
    syncStatusTitle.font = [UIFont boldSystemFontOfSize:16.f];
    syncStatusTitle.textColor = [UIColor blackColor];
    
    UILabel *syncStatusLabel = [[UILabel alloc]initWithFrame:CGRectMake(syncStatusTitle.right, logLabel.bottom + 10, 100, 20)];
    syncStatusLabel.text = @"-";
    syncStatusLabel.font = [UIFont systemFontOfSize:14.f];
    syncStatusLabel.textColor = [UIColor grayColor];
    
    UILabel *syncLabel = [[UILabel alloc]initWithFrame:CGRectMake(logLabel.left, logLabel.bottom + 10, 50, 20)];
    syncLabel.text = @"Sync:";
    
    UISwitch *syncSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(syncLabel.right, logLabel.bottom + 10, 50, 30)];
    syncSwitch.on = _syncEnable;
    [syncSwitch addTarget:self action:@selector(handleSyncSwitch:) forControlEvents:UIControlEventTouchUpInside];
    
    
    UILabel *logFilePathTitle = [[UILabel alloc]initWithFrame:CGRectMake(edge, syncStatusTitle.bottom + 10, 80, 20)];
    logFilePathTitle.text = @"File Path: ";
    logFilePathTitle.font = [UIFont boldSystemFontOfSize:16.f];
    logFilePathTitle.textColor = [UIColor blackColor];
    
    UILabel *logFilePathLabel = [[UILabel alloc]initWithFrame:CGRectMake(logFilePathTitle.right, syncStatusLabel.bottom + 10, 300, 20)];
    logFilePathLabel.text = @"-";
    logFilePathLabel.font = [UIFont systemFontOfSize:14.f];
    logFilePathLabel.textColor = [UIColor grayColor];
    
    
    CGRect frame = baseView.bounds;
    frame.origin.y = logFilePathTitle.bottom + 10;
    frame.size.height -= logFilePathLabel.bottom;
    UITableView *tableView = [[UITableView alloc] initWithFrame:frame style:UITableViewStylePlain];
    tableView.showsVerticalScrollIndicator = NO;
    tableView.dataSource = self;
    tableView.clipsToBounds = YES;
    tableView.scrollEnabled = YES;
    tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    tableView.rowHeight = DeviceMeasureCell.cellHeight;
    tableView.delegate = self;
    tableView.hidden = YES;
    self.tableView = tableView;
    
    [baseView addSubview:label];
    [baseView addSubview:modeLabel];
    [baseView addSubview:logLabel];
    [baseView addSubview:logSwitch];
    [baseView addSubview:syncStatusTitle];
    [baseView addSubview:syncStatusLabel];
    [baseView addSubview:syncLabel];
    [baseView addSubview:syncSwitch];
    [baseView addSubview:logFilePathTitle];
    [baseView addSubview:logFilePathLabel];
    [baseView addSubview:tableView];
    
    self.syncStatusLabel = syncStatusLabel;
    self.logFilePathLabel = logFilePathLabel;
    
}

/// Set the startFlag
- (void)setStartFlag:(BOOL)startFlag
{
    _startFlag = startFlag;
    if (startFlag)
    {
        [self.startButton setTitle:@"STOP" forState:UIControlStateNormal];
    }
    else
    {
        [self.startButton setTitle:@"START" forState:UIControlStateNormal];
    }
}

#pragma mark - Logic

/// showing the progress hud of synchronization.
- (void)showSyncingHud
{
    _syncingHud = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    _syncingHud.backgroundView.style = MBProgressHUDBackgroundStyleSolidColor;
    _syncingHud.backgroundView.color = [UIColor colorWithWhite:0.f alpha:0.1f];
    _syncingHud.label.text = NSLocalizedString(@"Syncing...", @"Sync title");
}

/// hide the progress hud
- (void)hideProgressHud
{
    [self.syncingHud hideAnimated:YES];
}

/// Start the real-time streaming
/// This will start after sychronization success
- (void)startMeasure
{
    self.startFlag = YES;
    self.tableView.hidden = NO;
    for (XsensDotDevice *device in self.measureDevices)
    {
        device.plotMeasureMode = XSBleDevicePayloadCompleteEuler;
        device.plotLogEnable = self.logEnable;
        device.plotMeasureEnable = YES;
    }
}

/// Stop real-time streaming
- (void)stopMeasure
{
    self.startFlag = NO;
    for (XsensDotDevice *device in self.measureDevices)
    {
        device.plotMeasureEnable = NO;
    }
}

/// Start synchronization
/// We have the sychronization before real-time streaming to synchronous Data
- (void)startSync
{
    __weak __typeof(self) wself = self;
    XsensDotSyncResultBolck block = ^(NSArray *array)
    {
        for (int i = 0; i < array.count; i++)
        {
            NSDictionary *resultDic = array[i];
            wself.syncResult |= [[resultDic objectForKey:@"success"] boolValue];
        }
        
        [wself hideProgressHud];
        if (wself.syncResult)
        {
            wself.syncStatusLabel.text = @"Success";
            [wself startMeasure];
        }
        else
        {
            wself.syncStatusLabel.text = @"Fail";
        }
    };
    
    [self showSyncingHud];
    [XsensDotSyncManager startSync:self.measureDevices result:block];
}

/// Start heading reset or revert
- (void)startHeading
{
    for (XsensDotDevice *device in self.measureDevices) {
        if (device.isSupportHeadingReset)
        {
            device.headingResetResult = ^(int result) {
                NSLog(@"Heading result %d", result);
                result != 0? [self showHeadingSuccess] : [self showHeadingFail];
            };
            
            if (device.headingStatus == XSHeadingStatusXrmHeading)
            {
                [device startHeadingRevert];
            }
            else if (device.headingStatus == XSHeadingStatusXrmDefaultAlignment ||
                     device.headingStatus == XSHeadingStatusXrmNone){
                [device startHeadingReset];
            }
        }
    }
}

/// Show no sensor connected
- (void)showHeadingSuccess
{
    MBProgressHUD *hud =  [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.offset = CGPointMake(0, 200);
    hud.label.text = @"Heading success";
    [hud hideAnimated:YES afterDelay:1.0f];
}

/// Show no sensor connected
- (void)showHeadingFail
{
    MBProgressHUD *hud =  [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.offset = CGPointMake(0, 200);
    hud.label.text = @"Heading fail";
    [hud hideAnimated:YES afterDelay:1.0f];
}


#pragma mark - TouchEvent

/// Handle the START button tapped
- (void)handleStartButton:(UIButton *)sender
{
    if (self.startFlag)
    {
        [self stopMeasure];
    }
    else
    {
        if (self.syncEnable)
        {
            [self startSync];
        }
        else
        {
            [self startMeasure];
        }
    }
}

/// Handle the Log switch   tapped
- (void)handleLogSwitch:(UISwitch *)sender
{
    self.logEnable = sender.on;
}

/// Handle sync switch button tapped
- (void)handleSyncSwitch:(UISwitch *)sender
{
    self.syncEnable = sender.on;
}


#pragma mark - Notification

/// Receive  the notification kXsensDotNotificationDeviceLoggingPath
- (void)onLogPathReceive:(NSNotification *)sender
{
    NSString *logText = [NSString stringWithFormat:@"APP -> Logs -> %@",sender.object];
    self.logFilePathLabel.text = logText;
}

/// Add the notification for Log file path
- (void)addObserver
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(onLogPathReceive:) name:kXsensDotNotificationDeviceLoggingPath object:nil];
}

/// Remove the notification for Log file path
- (void)removeObserver
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center removeObserver:self name:kXsensDotNotificationDeviceLoggingPath object:nil];
}

#pragma mark -- UITableViewDataSource &  UITableViewDelegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.measureDevices.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *indentifier = [DeviceMeasureCell cellIdentifier];;
    DeviceMeasureCell *cell = [tableView dequeueReusableCellWithIdentifier:indentifier];
    if (cell == nil)
    {
        cell = [[DeviceMeasureCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:indentifier];
    }
    
    cell.device = self.measureDevices[indexPath.row];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return DeviceMeasureCell.cellHeight;
}
@end
