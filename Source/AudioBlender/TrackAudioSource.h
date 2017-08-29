/*
  ==============================================================================

    TrackAudioSource.h
    Created: 20 Jun 2016 8:34:31pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef TRACKAUDIOSOURCE_H_INCLUDED
#define TRACKAUDIOSOURCE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AudioBlender;

class TrackAudioSource: public PositionableAudioSource{
public:
    TrackAudioSource(const AudioBlender* pAudioBlender, AudioFormatReaderSource* pAudioReaderSource, AudioThumbnail* pThumbnail);
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
    
    /** Returns true if this source is muted. */
    bool isMute() const;
    
    /** Tells the source whether you'd like to be Mute */
    void setMute(bool shouldMute);
    
    /** Returns true if this source is soloed. */
    bool isSolo() const;
    
    /** Tells the source whether you'd like to be Solo */
    void setSolo(bool shouldSolo);
    
    AudioThumbnail* getAudioThumbnail()const;
private:
    //==============================================================================
    ScopedPointer<AudioFormatReaderSource> _pAudioReaderSource;
    ScopedPointer<AudioThumbnail> _pThumbnail;
    const AudioBlender* _pAudioBlender;
    CriticalSection lock;
    AudioSampleBuffer tempBuffer;
    double currentSampleRate;
    int bufferSizeExpected;
    
    bool _bIsMute;
    bool _bIsSolo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackAudioSource)
};



#endif  // TRACKAUDIOSOURCE_H_INCLUDED
