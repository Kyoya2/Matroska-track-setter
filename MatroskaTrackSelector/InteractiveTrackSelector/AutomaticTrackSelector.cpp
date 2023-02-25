#include "AutomaticTrackSelector.h"

void AutomaticTrackSelector::mark_subtitle_track_for_selection(const size_t track_index)
{
    m_selected_subtitle_track_index = track_index;
    if (m_selected_audio_track_index != -1)
    {
        this->TrackManager::set_default_tracks(m_selected_subtitle_track_index, m_selected_audio_track_index);
    }
}

void AutomaticTrackSelector::mark_audio_track_for_selection(const size_t track_index)
{
    m_selected_audio_track_index = track_index;
    if (m_selected_subtitle_track_index != -1)
    {
        this->TrackManager::set_default_tracks(m_selected_subtitle_track_index, m_selected_audio_track_index);
    }
}
