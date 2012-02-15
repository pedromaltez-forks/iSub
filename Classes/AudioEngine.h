//
//  AudioEngine.h
//  iSub
//
//  Created by Ben Baron on 11/16/11.
//  Copyright (c) 2011 Ben Baron. All rights reserved.
//

#import "bass.h"
#import "bassflac.h"
#import "bass_fx.h"
#import "bassmix.h"
#import <AudioToolbox/AudioToolbox.h>

#define ISMS_BASSBufferSize 400
#define ISMS_defaultSampleRate 44100


//#define ISMS_AQBufferSizeInFrames 512
//#define ISMS_AQNumBuffers 4
//#define ISMS_AQBytesToWaitForAudioData (1024 * 160) // 5 seconds of audio in a 320kbps stream

// Stream create failure retry values
#define RETRY_DELAY 2.0
#define MIN_FILESIZE_TO_FAIL (1024 * 1024 * 3)

#define ISMS_NumSecondsToWaitForAudioData 5;

typedef enum
{
	ISMS_BASS_EQ_DATA_TYPE_none,
	ISMS_BASS_EQ_DATA_TYPE_fft,
	ISMS_BASS_EQ_DATA_TYPE_line
} ISMS_BASS_EQ_DATA_TYPE;

typedef enum
{
	ISMS_AE_STATE_off,
	ISMS_AE_STATE_playing,
	ISMS_AE_STATE_paused,
	ISMS_AE_STATE_stopped,
	ISMS_AE_STATE_waitingForData,
	ISMS_AE_STATE_waitingForDataNoResume,
	ISMS_AE_STATE_finishedWaitingForData
} ISMS_AE_STATE;

@class Song, BassParamEqValue, PlaylistSingleton, BassUserInfo;
@interface AudioEngine : NSObject
{
	// Equalizer
	NSMutableArray *eqValueArray, *eqHandleArray;
	float fftData[1024];
	short *lineSpecBuf;
	int lineSpecBufSize;
	ISMS_BASS_EQ_DATA_TYPE eqDataType;
	
	// BASS streams
	BOOL BASSisFilestream1;
	HSTREAM fileStream1;
	HSTREAM fileStreamTempo1;
	HSTREAM fileStream2;
	HSTREAM fileStreamTempo2;
	HSTREAM outStream;
	HFX volumeFx;
}

+ (AudioEngine *)sharedInstance;

// Playback methods
//
- (void)startWithOffsetInBytes:(NSNumber *)byteOffset orSeconds:(NSNumber *)seconds;
- (void)seekToPositionInBytes:(QWORD)bytes inStream:(HSTREAM)stream;
- (void)seekToPositionInBytes:(QWORD)bytes;
- (void)seekToPositionInSeconds:(NSUInteger)seconds inStream:(HSTREAM)stream;
- (void)seekToPositionInSeconds:(NSUInteger)seconds;
- (void)start;
- (void)stop;
- (void)pause;
- (void)playPause;

// BASS methods
//
- (unsigned long long)preSilenceLengthForSong:(Song *)aSong;
- (void)bassInit:(NSUInteger)sampleRate;
- (void)bassInit;
- (BOOL)bassFree;
- (void)prepareNextSongStreamInBackground;
- (void)prepareNextSongStream;
- (void)clearEqualizerValuesFromStream:(HSTREAM)stream;
- (void)clearEqualizerValues;
- (void)applyEqualizerValues:(NSArray *)values toStream:(HSTREAM)stream;
- (void)applyEqualizerValues:(NSArray *)values;
- (BOOL)toggleEqualizer;
- (void)updateEqParameter:(BassParamEqValue *)value;
- (BassParamEqValue *)addEqualizerValue:(BASS_DX8_PARAMEQ)value;
- (NSArray *)removeEqualizerValue:(BassParamEqValue *)value;
- (void)removeAllEqualizerValues;
- (void)readEqData;
- (float)fftData:(NSUInteger)index;
- (short)lineSpecData:(NSUInteger)index;
- (void)bassSetGainLevel:(float)gain;
- (uint32_t)bassGetOutputData:(void *)buffer length:(uint32_t)length;
- (NSInteger)bassSampleRate;
- (NSInteger)bassStreamSampleRate:(HSTREAM)stream;
- (NSInteger)preferredSampleRate:(NSUInteger)sampleRate;

@property (readonly) BOOL isPlaying;
@property (readonly) NSInteger bitRate;
@property (readonly) QWORD currentByteOffset;
@property (readonly) double progress;
@property (readonly) BOOL isEqualizerOn;
@property (readonly) NSArray *equalizerValues;
@property unsigned long long startByteOffset;
@property double startSecondsOffset;
@property HSTREAM currentStream;
@property HSTREAM currentStreamTempo;
@property (readonly) HSTREAM currentReadingStream;
@property HSTREAM nextStream;
@property HSTREAM nextStreamTempo;
@property (readonly) HSTREAM nextReadingStream;
@property HSTREAM presilenceStream;
@property (retain) PlaylistSingleton *currPlaylistDAO;
@property (retain) NSThread *fftDataThread;
@property BOOL isFftDataThreadToTerminate;
@property BOOL isFastForward;
@property BOOL audioQueueShouldStopWaitingForData;
@property ISMS_AE_STATE state;
@property NSInteger audioSessionSampleRate;
@property NSInteger bassReinitSampleRate;
@property NSUInteger bufferLengthMillis;
@property NSUInteger bassUpdatePeriod;

const char *GetCTypeString(DWORD ctype, HPLUGIN plugin);

- (void)readEqDataInternal;
- (void)stopReadingEqData;
- (void)startReadingEqData:(ISMS_BASS_EQ_DATA_TYPE)type;

@end