using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System;

public class SceneTransition : MonoSingleton<SceneTransition>
{
    string cutsceneName = "title";
    private Action action;

    public Action GetAction() { return action; }
    public string GetCutScenename() { return cutsceneName; }
    public void LoadCutScene(string cutSceneAnimation,Action action_ = null)
    {
        action = action_;
        cutsceneName = cutSceneAnimation;
        SceneManager.LoadScene("CutScene");
    }

    public void LoadScene(string name)
    {
        SceneManager.LoadScene(name);
    }
}
