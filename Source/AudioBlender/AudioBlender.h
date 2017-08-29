/*
  ==============================================================================

    AudioBlender.h
    Created: 17 Jun 2016 9:46:29pm
    Author:  Charan DSouza

  ==============================================================================
*/

#ifndef AUDIOBLENDER_H_INCLUDED
#define AUDIOBLENDER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class TrackAudioSource;

class AudioBlenderDelegate{
public:
    virtual ~AudioBlenderDelegate(){}
    virtual void TrackAdded(const TrackAudioSource* pTrackAudioSource) = 0;
    virtual void TrackDeleted(const TrackAudioSource* pTrackAudioSource) = 0;
    
    virtual void UpdatePosition() = 0;
};

class AudioBlender: public PositionableAudioSource{
public:
    AudioBlender(AudioBlenderDelegate& delegate);
    ~AudioBlender();
    
    void addTrack( const juce::File& audioFile );
    void deleteTrack(TrackAudioSource* const pTrackAudioSource );
    
    void PlayStop();
    
    //==============================================================================
    /** Adds an input source to the mixer.
     
     If the mixer is running you'll need to make sure that the input source
     is ready to play by calling its prepareToPlay() method before adding it.
     If the mixer is stopped, then its input sources will be automatically
     prepared when the mixer's prepareToPlay() method is called.
     
     @param newInput             the source to add to the mixer
     @param deleteWhenRemoved    if true, then this source will be deleted when
     no longer needed by the mixer.
     */
    void addInputSource (TrackAudioSource* newInput, bool deleteWhenRemoved);
    
    /** Removes an input source.
     If the source was added by calling addInputSource() with the deleteWhenRemoved
     flag set, it will be deleted by this method.
     */
    void removeInputSource (TrackAudioSource* const input);
    
    /** Removes all the input sources.
     Any sources which were added by calling addInputSource() with the deleteWhenRemoved
     flag set will be deleted by this method.
     */
    void removeAllInputs();
    
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
    
    void setSoloTrack( TrackAudioSource* pTrackAudioSource , const bool shouldSolo );

    bool HasSolo() const;
    /** Returns the total length of the stream (in milliseconds). */
    int64 getTotalDuration() const;
    
    bool isPlaying() const;
private:
    //==============================================================================
    Array<TrackAudioSource*> inputs;
    BigInteger inputsToDelete;
    CriticalSection lock;
    AudioSampleBuffer tempBuffer;
    double currentSampleRate;
    int bufferSizeExpected;
    int64 _iNextReadPosition;
    
    bool _bShouldLoop;
    AudioBlenderDelegate& _delegate;
    AudioDeviceManager _deviceManager;
    AudioSourcePlayer _audioSourcePlayer;
    AudioTransportSource _audioTransportSource;
    AudioFormatManager _formatManager;
    AudioThumbnailCache _thumbnailCache;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioBlender)
};
#endif  // AUDIOBLENDER_H_INCLUDED