//
//  MfmViewController.m
//  XsensDotExampleiOS
//
//  Created by Jayson on 2021/11/30.
//  Copyright © 2021 Xsens. All rights reserved.
//

#import "MfmViewController.h"
#import "DeviceMfmCell.h"
#import <XsensDotSdkMfm/XsensDotMFMManager.h>
#import <XsensDotSdk/XsensDotConnectionManager.h>

/**
 * This is the demo for the sensors to do the MFM function
 * When  MFM is started ,we must wait the process finished.
 * Start MFM and Stop MFM is very easy, we can call startMFM and stopMFM directyly, then we need to listen the XsensDotMFMDelegate interfaces.
 */
@interface MfmViewController ()<UITableViewDelegate, UITableViewDataSource, XsensDotMFMDelegate, XsensDotConnectionDelegate>

@property (strong, nonatomic) UITableView *tableView;
@property (strong, nonatomic) UIButton *startButton;
/// This flag indicates the MFM is started or not.
@property (assign, nonatomic) BOOL startFlag;
/// This flag indicates if current ViewController can exit or not.
/// If MFM is being processed, the current viewController can not exit.
@property (assign, nonatomic) BOOL exitFlag;

/// this array add device mfm status and decide the bottom button if can stop mfm.
/// [ {"address" : "D4:CA:6E:F1:76:DE", "status" : "XSDeviceMFMStateProcessing" } ]
@property (strong, nonatomic) NSMutableArray *stateArray;

@end

@implementation MfmViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self localInfoSetup];
    [self navigationItemsSetup];
    [self setupViews];
    [self backButtonListener];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [[XsensDotMFMManager defaultManager] setMfmDelegate:self];
    [XsensDotConnectionManager setConnectionDelegate:self];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    if ([self.navigationController respondsToSelector:@selector(interactivePopGestureRecognizer)])
    {
        self.navigationController.interactivePopGestureRecognizer.enabled = NO;
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    self.navigationController.interactivePopGestureRecognizer.enabled = YES;
    if (self.exitFlag)
    {
        for (XsensDotDevice *device in self.mfmDevices)
        {
            [device setOutputRate:device.outputRate filterIndex:device.filterIndex];
        }
    }
}

- (void)localInfoSetup
{
    [self initStateArray];
}

/// Init the MFM state array
- (void)initStateArray
{
    _stateArray = [NSMutableArray new];
    for (XsensDotDevice *device in self.mfmDevices)
    {
        NSMutableDictionary *statusDic = [NSMutableDictionary dictionaryWithObjectsAndKeys:device.macAddress, @"address", [NSNumber numberWithInt:XSDeviceMFMStateDefault],@"status", nil];
        [_stateArray addObject:statusDic];
    }
}

- (void)navigationItemsSetup
{
    self.title = @"Mag Field Mapper";
    UINavigationBar *navigationBar = self.navigationController.navigationBar;
    navigationBar.tintColor = [UIColor whiteColor];
}

- (void)backButtonListener
{
    UIView *leftBarView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 120, 44)];
    
    UIButton *backButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 30, 44)];
    [backButton addTarget:self action:@selector(backBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [backButton setImage:[UIImage imageNamed:@"ic_back"] forState:UIControlStateNormal];
    backButton.contentMode = UIViewContentModeLeft;
    backButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
    [leftBarView addSubview:backButton];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc]initWithCustomView:backButton];
}

- (void)setupViews
{
    UIView *baseView = self.view;
    CGFloat horizontalEdge = 16;
    self.edgesForExtendedLayout = UIRectEdgeBottom;
    baseView.backgroundColor = [UIColor whiteColor];
    
    // Bottom Start button Layout
    CGFloat startButtonHeight = 40;
    CGFloat bottomViewY = baseView.height - UINavigationBarHeight - startButtonHeight - 5;
    
    CGRect frame = CGRectMake(0, 5, baseView.width, bottomViewY);
    UITableView *tableView = [[UITableView alloc] initWithFrame:frame style:UITableViewStylePlain];
    tableView.backgroundColor = [UIColor whiteColor];
    tableView.dataSource = self;
    tableView.delegate = self;
    tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    [baseView addSubview:tableView];
    self.tableView = tableView;
    
    if([UIDevice isIPhoneXSeries])
    {
        bottomViewY -= UIStatusBarHeightForIPhoneX + 24;
    }else
    {
        bottomViewY -= UIStatusBarHeightCommon;
    }
    UIButton *startButton = [UIButton buttonWithType:UIButtonTypeSystem];
    startButton.frame = CGRectMake(horizontalEdge, bottomViewY, baseView.width - horizontalEdge * 2, startButtonHeight);
    startButton.backgroundColor = UIColor.orangeColor;
    [startButton setTitle:@"Start MFM" forState:UIControlStateNormal];
    [startButton setTintColor:[UIColor whiteColor]];
    startButton.layer.cornerRadius = 3;
    [startButton addTarget:self action:@selector(startStopButtonTap:) forControlEvents:UIControlEventTouchUpInside];
    self.startButton = startButton;
    
    [baseView addSubview:startButton];
}

/// Set current MFM process is started or not.
- (void)setStartFlag:(BOOL)startFlag
{
    _startFlag = startFlag;
    if (startFlag)
    {
        [self.startButton setTitle:@"Stop MFM" forState:UIControlStateNormal];
    }
    else
    {
        _exitFlag = YES;
        [self.startButton  setTitle:@"Exit MFM" forState:UIControlStateNormal];
    }
}

#pragma mark - UI

/// Update tableview cell status when disconnect
- (void)updateCellDisconnect:(XsensDotDevice *)device
{
    NSArray *cells = self.tableView.visibleCells;
    if(cells.count > 0)
    {
        for(DeviceMfmCell *cell in cells)
        {
            if ([cell.device.macAddress isEqualToString:device.macAddress])
            {
                [cell cellDisconnected];
            }
        }
    }
}

/// Update tableview cell status when start MFM
- (void)updateCellStartMFM
{
    NSArray *cells = self.tableView.visibleCells;
    if (cells.count > 0)
    {
        for(DeviceMfmCell *cell in cells)
        {
            [cell cellInProgress:0];
        }
    }
}

/// Update tableview cell status when stop MFM
- (void)updateCellStopMFM
{
    NSArray *cells = self.tableView.visibleCells;
    if (cells.count > 0)
    {
        for(DeviceMfmCell *cell in cells)
        {
            for (NSMutableDictionary *stateDic in self.stateArray)
            {
                XSDeviceMFMState state = (XSDeviceMFMState)[[stateDic objectForKey:@"status"] intValue];
                NSString *macAddress = [stateDic objectForKey:@"address"];
                if ([cell.device.macAddress isEqualToString:macAddress])
                {
                    if (state == XSDeviceMFMStateStart)
                    {
                        [cell cellStopped];
                    }
                }
            }
        }
    }
}

/// Update bottom start buttom status
- (void)updateStartButtonStatus
{
    BOOL canStop = NO;
    BOOL canStart = YES;
    
    int completeCount = 0;
    
    for (NSMutableDictionary *stateDic in self.stateArray)
    {
        XSDeviceMFMState state = (XSDeviceMFMState)[[stateDic objectForKey:@"status"] intValue];
        if (state == XSDeviceMFMStateDefault || state == XSDeviceMFMStateStart)
        {
            canStop = YES;
        }
        if (state == XSDeviceMFMStateComplete)
        {
            completeCount ++;
        }
        
        if (state == XSDeviceMFMStateProcessing)
        {
            canStart = NO;
        }
    }
    
    if (self.startFlag)
    {
        if (completeCount == self.mfmDevices.count)
        {
            self.startFlag = NO;
            self.startButton.enabled = YES;
        }
        else
        {
            self.startButton.enabled = canStop;
        }
    }
    else
    {
        self.startButton.enabled = canStart;
    }
}

#pragma mark - Logic

/// Start MFM 
- (void)startMFM
{
    self.startFlag = YES;
    [self updateCellStartMFM];
    /// The start MFM sdk method, parameter is XsensDotDevice list.
    [[XsensDotMFMManager defaultManager] startMFM:self.mfmDevices];
    for (NSMutableDictionary *dic in self.stateArray)
    {
        [dic setObject:[NSNumber numberWithInt:XSDeviceMFMStateStart] forKey:@"status"];
    }
}

/// Stop MFM
- (void)stopMFM
{
    self.startFlag = NO;
    [self updateCellStopMFM];
    /// The stop MFM sdk method, parameter is XsensDotDevice list.
    [[XsensDotMFMManager defaultManager] stopMFM:self.mfmDevices];
    [self updateStartButtonStatus];
}

/// Exit MFM view controller
- (void)exitMFM
{
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - TouchEvent

/// The bottom start/stop/exit button touch event.
- (void)startStopButtonTap:(UIButton *)sender
{
    if (self.exitFlag)
    {
        [self exitMFM];
    }
    else
    {
        self.startFlag? [self stopMFM] : [self startMFM];
    }
}

/// The left  back button on navigation  touch event
- (void)backBtnClicked:(UIButton *)sender
{
    if (self.startFlag)
    {
//        self.noticeText = @"Stop MFM to exit this page";
    }
    else
    {
        [self.navigationController popViewControllerAnimated:YES];
    }
}

#pragma mark - XsensDotMFMDelegate

/**
 * This method will be triggered after call the startMFM. we can observe the progress of MFM though the mac address
 * @param progress The MFM progress
 * @param address The XsensDotDevice mac address
 */
- (void)onMFMProgress:(int)progress address:(NSString *)address
{
    NSArray *cells = self.tableView.visibleCells;
    if(cells.count > 0)
    {
        for(DeviceMfmCell *cell in cells)
        {
            if ([cell.device.macAddress isEqualToString:address])
            {
                [cell cellInProgress:progress];
                if (progress == 100)
                {
                    for (NSMutableDictionary *dic in self.stateArray)
                    {
                        if ([[dic objectForKey:@"address"] isEqualToString:address])
                        {
                            [dic setObject:[NSNumber numberWithInt:XSDeviceMFMStateProcessing] forKey:@"status"];
                        }
                    }
                }
            }
        }
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self updateStartButtonStatus];
    });
}

/**
 * When MFM finished, this method will be triggered.
 * @param type The MFM result type.
 * @param address The XsensDotDevice mac address
 */
- (void)onMFMCompleted:(XSDotMFMResultTpye)type address:(NSString *)address
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSArray *cells = self.tableView.visibleCells;
        if(cells.count > 0)
        {
            for(DeviceMfmCell *cell in cells)
            {
                if ([cell.device.macAddress isEqualToString:address])
                {
                    if (type == XSDotMFMResultAcceptable || type == XSDotMFMResultGood)
                    {
                        [cell cellFinished];
                    }
                    else
                    {
                        [cell cellFailed];
                    }
                    for (NSMutableDictionary *dic in self.stateArray)
                    {
                        if ([[dic objectForKey:@"address"] isEqualToString:address])
                        {
                            [dic setObject:[NSNumber numberWithInt:XSDeviceMFMStateComplete] forKey:@"status"];
                        }
                    }
                }
            }
        }
        [self updateStartButtonStatus];
    });
    
}

#pragma mark - XsensDotConnectionDelegate

/// XsensDot device disconnected
/// @param device XsensDotDevice
- (void)onDeviceDisconnected:(XsensDotDevice *)device
{
    [self updateCellDisconnect:device];
}

#pragma mark - UITableViewDataSource &  UITableViewDelegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.mfmDevices.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return DeviceMfmCell.cellHeight;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *indentifier = [NSString stringWithFormat:@"%@%zd%zd", DeviceMfmCell.cellIdentifier, [indexPath section], [indexPath row]];
    DeviceMfmCell *cell = [tableView dequeueReusableCellWithIdentifier:indentifier];
    
    if (cell == nil)
    {
        cell = [[DeviceMfmCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:indentifier];
        cell.device = self.mfmDevices[indexPath.row];
    }
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
}

@end
