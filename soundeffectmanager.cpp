// soundeffectmanager.cpp
#include "soundeffectmanager.h"

SoundEffectManager* SoundEffectManager::m_instance = nullptr;

SoundEffectManager::SoundEffectManager(QObject *parent) : QObject(parent)
{
    m_backgroundMusicPlayer.setSource(QUrl::fromLocalFile("://sounds/anExcerptOnCherryBlossoms.wav"));

    m_collisionPlayer.setSource(QUrl::fromLocalFile("://sounds/ding.wav"));

    m_missPlayer.setSource(QUrl::fromLocalFile("://sounds/sadWhistle.wav"));

    m_soundEffects.append(&m_collisionPlayer);

    m_soundEffects.append(&m_missPlayer);
}

SoundEffectManager* SoundEffectManager::instance()
{
    if (!m_instance) {
        m_instance = new SoundEffectManager();
    }
    return m_instance;
}


void SoundEffectManager::playCollisionSound()
{
    if(!isSoundManagerFree()) {
        return;
    }
    m_collisionPlayer.play();
}

void SoundEffectManager::playMissSound()
{
    if(!isSoundManagerFree()) {
        return;
    }
    m_missPlayer.play();
}

void SoundEffectManager::playBackgroundMusic() {
    if(m_backgroundMusicPlayer.isPlaying()) {
        return;
    }

    m_backgroundMusicPlayer.setLoopCount(QSoundEffect::Infinite);

    m_backgroundMusicPlayer.play();
}

bool SoundEffectManager::isSoundManagerFree() {
    for (QSoundEffect* soundEffect : m_soundEffects) {
        if (soundEffect->isPlaying()) {
            return false;
        }
    }
    return true;
}


SoundEffectManager::~SoundEffectManager()
{
    m_instance = nullptr;
}
