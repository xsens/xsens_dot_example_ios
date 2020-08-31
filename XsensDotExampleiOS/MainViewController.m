//
//  MainViewController.m
//  XsensDotDebug
//
//  Created by Jayson on 2020/6/5.
//  Copyright © 2020 Xsens. All rights reserved.
//

#import "MainViewController.h"
#import "DeviceConnectCell.h"
#import "UIDeviceCategory.h"
#import "UIViewCategory.h"
#import "MeasureViewController.h"
#import <MJRefresh/MJRefresh.h>
#import <XsensDotSdk/XsensDotDevice.h>
#import <XsensDotSdk/XsensDotLog.h>
#import <XsensDotSdk/XsensDotDevicePool.h>
#import <XsensDotSdk/XsensDotConnectionManager.h>
#import <XsensDotSdk/XsensDotReconnectManager.h>
#import <MBProgressHUD.h>

@interface MainViewController ()<UITableViewDelegate,UITableViewDataSource, XsensDotConnectionDelegate>

@property (strong, nonatomic) UITableView *tableView;
@property (strong, nonatomic) NSMutableArray *deviceList;
@property (strong, nonatomic) NSMutableArray *connectList;
@property (strong, nonatomic) UIButton *measureButton;

@end

@implementation MainViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    /// Set xsensDot connection delete
    [XsensDotConnectionManager setConnectionDelegate:self];
    /// Set log enable
    [XsensDotLog setLogEnable:YES];
    /// Set reconnection enable
    [XsensDotReconnectManager setEnable:YES];
    /// Add notifications
    [self addObservers];
    
    /// Refresh tableview back from MeasureViewController
    if (self.connectList.count != 0)
    {
        [self.tableView reloadData];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.tableView.mj_header endRefreshing];
    /// Stop ble scan
    [XsensDotConnectionManager stopScan];
    /// Remove notifications
    [self removeObservers];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.deviceList = [NSMutableArray arrayWithCapacity:20];
    self.connectList = [NSMutableArray arrayWithCapacity:20];
    [self navigationItemsSetup];
    [self setupViews];
}

- (void)navigationItemsSetup
{
    self.title = @"XsensDOT Example";
    UINavigationBar *navigationBar = self.navigationController.navigationBar;
    navigationBar.titleTextAttributes = @{NSForegroundColorAttributeName:[UIColor whiteColor]};
    navigationBar.barTintColor = [UIColor orangeColor];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:self.measureButton];
}


- (void)setupViews
{
    UIView *baseView = self.view;
    MJRefreshNormalHeader *header = [MJRefreshNormalHeader headerWithRefreshingBlock:^{
        [self scanDevices];
    }];
    header.lastUpdatedTimeLabel.hidden = YES;
    header.stateLabel.hidden = YES;
    
    CGRect frame = baseView.bounds;
    
    UITableView *tableView = [[UITableView alloc] initWithFrame:frame style:UITableViewStylePlain];
    tableView.showsVerticalScrollIndicator = NO;
    tableView.dataSource = self;
    tableView.delegate = self;
    tableView.mj_header = header;
    self.tableView = tableView;
    
    [baseView addSubview:tableView];
}

- (UIButton *)measureButton
{
    if (_measureButton == nil)
    {
        _measureButton = [UIButton buttonWithType:UIButtonTypeSystem];
        [_measureButton setTitle:@"Measure" forState:UIControlStateNormal];
        [_measureButton setTintColor:[UIColor whiteColor]];
        _measureButton.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightBold];
        [_measureButton addTarget:self action:@selector(handleMeasure:) forControlEvents:UIControlEventTouchUpInside];
    }
    return _measureButton;
}

/// Update UITableViewCell status
- (void)updateDeviceCellStatus
{
    NSArray *cells = self.tableView.visibleCells;
    if(cells.count > 0)
    {
        for(DeviceConnectCell *cell in cells)
        {
            [cell refreshDeviceStatus];
        }
    }
}

/// Start ble scan
- (void)scanDevices
{
    if(![XsensDotConnectionManager managerStateIsPoweredOn])
    {
        [self.tableView.mj_header endRefreshing];
        NSLog(@"Please enable bluetoooth first");
        return;
    }
    [self.deviceList removeAllObjects];
    if (self.connectList.count != 0)
    {
        [self.deviceList addObjectsFromArray:self.connectList];
    }
    [self.tableView reloadData];
    /// Start scan
    [XsensDotConnectionManager scan];
}

#pragma mark -- Logic

/// Disconnect all sensors.
- (void)disconnectAll
{
    for (XsensDotDevice *device in self.connectList)
    {
        [XsensDotConnectionManager disconnect:device];
    }
}

/// Show no sensor connected
- (void)showUnconnectHud
{
    MBProgressHUD *hud =  [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
    hud.mode = MBProgressHUDModeText;
    hud.offset = CGPointMake(0, 200);
    hud.label.text = @"Please connect at least a sensor";
    [hud hideAnimated:YES afterDelay:1.0f];
}

#pragma mark -- TouchEvent

/// Handle the switch button of UITableViewCell tapped
- (void)onCellConnectButtonTapped:(DeviceConnectCell *)cell
{
    XsensDotDevice *device = cell.device;
    if(device.state != CBPeripheralStateConnected)
    {
        [self.connectList addObject:device];
        /// connect a sensor
        [XsensDotConnectionManager connect:device];
        /// add to DevicePool.
        /// Reconnection has Two conditions,please also unbind it after disconnected .
        /// 1. [XsensDotReconnectManager setEnable:YES];
        /// 2. [XsensDotDevicePool bindDevice:device]
        [XsensDotDevicePool bindDevice:device];
    }
    else
    {
        [self.connectList removeObject:device];
        /// Disconnect the sensor
        [XsensDotConnectionManager disconnect:device];
        /// Remove from the DevicePool
        [XsensDotDevicePool unbindDevice:device];
    }
    
    [cell refreshDeviceStatus];
}

/// Handle measure button tapped
- (void)handleMeasure:(UIButton *)sender
{
    if (self.connectList.count == 0)
    {
        [self showUnconnectHud];
    }
    else
    {
        MeasureViewController *measureViewController = [MeasureViewController new];
        measureViewController.measureDevices = self.connectList;
        [self.navigationController pushViewController:measureViewController animated:YES];
    }
}

#pragma mark -- XSConnectionDelegate


/// Ble scan done
- (void)onScanCompleted
{
    [self.tableView.mj_header endRefreshing];
}

/// XsensDot device connect failed
/// @param device XsensDotDevice
- (void)onDeviceConnectFailed:(XsensDotDevice *)device
{
    [self updateDeviceCellStatus];
}

/// XsensDot device disconnected
/// @param device XsensDotDevice
- (void)onDeviceDisconnected:(XsensDotDevice *)device
{
    [self updateDeviceCellStatus];
}

/// XsensDot device connect success
/// @param device XsensDotDevice
- (void)onDeviceConnectSucceeded:(XsensDotDevice *)device
{
    [self updateDeviceCellStatus];
}

/// Discovered XsensDot device
/// @param device XsensDotDevice
- (void)onDiscoverDevice:(XsensDotDevice *)device
{
    NSInteger index = [self.deviceList indexOfObject:device];
    if(index == NSNotFound)
    {
        if(![self.deviceList containsObject:device])
        {
            [self.deviceList addObject:device];
            [self.tableView reloadData];
        }
    }
}

/// Listen changes in Bluetooth status
/// @param managerState  XSDotManagerState
- (void)onManagerStateUpdate:(XSDotManagerState)managerState
{
    [self updateDeviceCellStatus];
    if(managerState != XSDotManagerStatePoweredOn)
    {
        [self.tableView.mj_header endRefreshing];
    }
    else
    {
        if([UIApplication sharedApplication].applicationState != UIApplicationStateBackground)
        {
            [self.tableView.mj_header beginRefreshing];
        }
    }
}

#pragma mark -- Notification

/// Receive the notification of kXsensDotNotificationDeviceBatteryDidUpdate
- (void)onDeviceBatteryUpdated:(NSNotification *)sender
{
    [self updateDeviceCellStatus];
}

/// Receive the notification of kXsensDotNotificationDeviceNameDidRead
- (void)onDeviceTagRead:(NSNotification *)sender
{
    [self updateDeviceCellStatus];
}

/// Add notifications
- (void)addObservers
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center addObserver:self selector:@selector(onDeviceBatteryUpdated:) name:kXsensDotNotificationDeviceBatteryDidUpdate object:nil];
    [center addObserver:self selector:@selector(onDeviceTagRead:) name:kXsensDotNotificationDeviceNameDidRead object:nil];
}

/// Remove notifications
- (void)removeObservers
{
    NSNotificationCenter *center = [NSNotificationCenter defaultCenter];
    [center removeObserver:self name:kXsensDotNotificationDeviceBatteryDidUpdate object:nil];
    [center removeObserver:self name:kXsensDotNotificationDeviceNameDidRead object:nil];
}


#pragma mark -- UITableViewDataSource &  UITableViewDelegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.deviceList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *indentifier = [DeviceConnectCell cellIdentifier];;
    DeviceConnectCell *cell = [tableView dequeueReusableCellWithIdentifier:indentifier];
    if (cell == nil)
    {
        cell = [[DeviceConnectCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:indentifier];
        cell.connectAction = ^(DeviceConnectCell * _Nonnull cell) {
            [self onCellConnectButtonTapped:cell];
        };
    }
    
    cell.device = self.deviceList[indexPath.row];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{

}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return DeviceConnectCell.cellHeight;
}

@end
