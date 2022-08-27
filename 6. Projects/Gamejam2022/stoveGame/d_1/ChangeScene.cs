using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class ChangeScene : MonoBehaviour
{
    public void ChangeSceneBtn()
    {
        switch(this.gameObject.name)
        {
            case "PlayGame":
                SceneManager.LoadScene("GameScene");
                break;

            case "Restart":
                Reset();
                break;

            case "Quit":
                Application.Quit();
                break;

        }
    }
    private void Reset()
    {
        SceneManager.LoadScene("GameScene");

    }
}
