//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

#import <YapDatabase/YapDatabaseConnection.h>

NS_ASSUME_NONNULL_BEGIN

@protocol OWSDatabaseConnectionDelegate <NSObject>

- (BOOL)areSyncRegistrationsComplete;

- (void)readTransactionWillBegin;
- (void)readTransactionDidComplete;
- (void)readWriteTransactionWillBegin;
- (void)readWriteTransactionDidComplete;

@end

#pragma mark -

@interface OWSDatabaseConnection : YapDatabaseConnection

@property (atomic, weak) id<OWSDatabaseConnectionDelegate> delegate;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithDatabase:(YapDatabase *)database
                        delegate:(id<OWSDatabaseConnectionDelegate>)delegate NS_DESIGNATED_INITIALIZER;

#pragma mark - "Safe" Read Write

- (void)safeAsyncReadWriteWithBlock:(void (^)(YapDatabaseReadWriteTransaction *transaction))block
                    completionQueue:(nullable dispatch_queue_t)completionQueue
                    completionBlock:(nullable dispatch_block_t)completionBlock;

@end

NS_ASSUME_NONNULL_END