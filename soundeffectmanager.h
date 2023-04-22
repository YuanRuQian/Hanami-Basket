// soundeffectmanager.h
#ifndef SOUNDEFFECTMANAGER_H
#define SOUNDEFFECTMANAGER_H

#include <QObject>
#include <QSoundEffect>
#include <QAudioOutput>
#include <QMediaPlayer>

class SoundEffectManager : public QObject
{
    Q_OBJECT

public:
    static SoundEffectManager* instance(); // Static method to get the singleton instance

    void playCollisionSound();
    void playMissSound();

private:
    // Private constructor and destructor to prevent direct instantiation and deletion
    explicit SoundEffectManager(QObject *parent = nullptr);
    ~SoundEffectManager();

    // Singleton instance
    static SoundEffectManager* m_instance;

    // Media players for playing sound effects
    QSoundEffect m_collisionPlayer;
    QSoundEffect m_missPlayer;

    QList<QSoundEffect*> m_soundEffects;

    bool isSoundManagerFree();
};

#endif // SOUNDEFFECTMANAGER_H
