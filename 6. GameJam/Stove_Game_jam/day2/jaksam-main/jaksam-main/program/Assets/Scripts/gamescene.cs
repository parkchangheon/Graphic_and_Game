using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class gamescene : MonoBehaviour
{
    private void Start()
    {
        SoundMgr.instance.PlayBGM("gamesceneBGM");
    }

    public void Restart()
    {
        SceneTransition.instance.LoadScene("GameScene");
    }

    public void Exit()
    {
        Application.Quit();
    }

    public void EndingCutScene(int time)
    {
        //클리어 time별 컷씬 나누기 
        if (time == -1)// Lose cutScene
        {
            SceneTransition.instance.LoadCutScene("lose", () =>
            {
                SceneTransition.instance.LoadScene("TitleScene");
            });
        }

        //1 분 2분 2분이상
        else if (time < 60)
        {
            SceneTransition.instance.LoadCutScene("clear1", () =>
            {
                SceneTransition.instance.LoadScene("TitleScene");
            });
        }
        else if (time < 90)
        {
            SceneTransition.instance.LoadCutScene("clear2", () =>
            {
                SceneTransition.instance.LoadScene("TitleScene");
            });
        }
        else
        {
            SceneTransition.instance.LoadCutScene("clear3", () =>
            {
                SceneTransition.instance.LoadScene("TitleScene");
            });
        }
    }


}
