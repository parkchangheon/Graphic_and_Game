using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Title : MonoBehaviour
{
    private void Start()
    {
        SoundMgr.instance.PlayBGM("titleBGM");
    }
    public void StartGame()
   {
        SceneTransition.instance.LoadCutScene("title", () =>
		{
            SceneTransition.instance.LoadScene("Tutorial");
        }
		);
   }

    public void Exit()
    {
        Application.Quit();
    }
}
