// Copyright (C) 2018-2019 gamevanilla. All rights reserved.
// This code can only be used under the standard Unity Asset Store End User License Agreement,
// a copy of which is available at http://unity3d.com/company/legal/as_terms.

using System.Collections.Generic;
using UnityEngine;


public class SoundMgr : MonoSingleton<SoundMgr>
{
	public List<AudioClip> BGMClips;
	[SerializeField]
	AudioSource bgmSource;
	public List<AudioClip> AudioClips;
	private readonly Dictionary<string, AudioClip> nameToSound = new Dictionary<string, AudioClip>();
	public List<SoundFx> soundFxes;


	private void Start()
	{
		if(AudioClips == null)
        {
			Debug.Log("오디오 클립 없음");
			return;
		}
		foreach (var sound in AudioClips)
			nameToSound.Add(sound.name, sound);
	}

	public void PlayBGM(string soundName)
	{
		if (BGMClips == null || BGMClips.Count <= 0)
		{
			Debug.Log("BGM 사운드가 없음");
			return;
		}

		for(int i = 0; i < BGMClips.Count; i++)
        {
			if(BGMClips[i].name == soundName)
            {
				bgmSource.clip = BGMClips[i];
				bgmSource.Play();
				return;
            }
		}
		Debug.LogError("BGM Data ERROR");
	}
	public void StopBGM()
    {
		if (bgmSource.isPlaying)
			bgmSource.Stop();

	}


	public void PlaySoundFx(string soundName)
	{
        if (nameToSound.ContainsKey(soundName) == false)
        {
            Debug.LogError("No sound data : " + soundName);
            return;
        }

        var clip = nameToSound[soundName];
        if (clip != null)
        {
			PlaySoundFx(clip);
		}
	}

	private void PlaySoundFx(AudioClip clip)
	{
		if (clip == null)
			return;
		
		for(int i = 0; i< soundFxes.Count; i++)
        {
			if(soundFxes[i].gameObject.activeSelf == false)
            {
				soundFxes[i].gameObject.SetActive(true);
				soundFxes[i].Play(clip);
				return;
			}
		}

		Debug.LogError("모든 AudioSource 사용중!!");
	}

}
