//
//  TrackAudioSource.hpp
//  Shruti
//
//  Created by Charan DSouza on 20/06/16.
//
//

#ifndef TrackAudioSource_hpp
#define TrackAudioSource_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class TrackAudioSource: public PositionableAudioSource{
public:
    TrackAudioSource( AudioFormatReaderSource* pAudioReaderSource );
    ~TrackAudioSource();
    
    //==============================================================================
    /** Implementation of the AudioSource method.
     This will call prepareToPlay() on all its input sources.
     */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    /** Implementation of the AudioSource method.
     This will call releaseResources() on all its input sources.
     */
    void releaseResources() override;
    
    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo&) override;
    
    //==============================================================================
    /** Tells the stream to move to a new position.
     
     Calling this indicates that the next call to AudioSource::getNextAudioBlock()
     should return samples from this position.
     
     Note that this may be called on a different thread to getNextAudioBlock(),
     so the subclass should make sure it's synchronised.
     */
    void setNextReadPosition (int64 newPosition) override;
    
    /** Returns the position from which the next block will be returned.
     
     @see setNextReadPosition
     */
    int64 getNextReadPosition() const override;
    
    /** Returns the total length of the stream (in samples). */
    int64 getTotalLength() const override;
    
    /** Returns true if this source is actually playing in a loop. */
    bool isLooping() const override;
    
    /** Tells the source whether you'd like it to play in a loop. */
    void setLooping (bool shouldLoop) override;
private:
    //==============================================================================
    ScopedPointer<AudioFormatReaderSource> _pAudioReaderSource;
    CriticalSection lock;
    AudioSampleBuffer tempBuffer;
    double currentSampleRate;
    int bufferSizeExpected;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackAudioSource)
};

#endif /* TrackAudioSource_hpp */\
