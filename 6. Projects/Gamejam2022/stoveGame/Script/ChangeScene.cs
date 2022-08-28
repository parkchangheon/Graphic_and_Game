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
                Debug.Log("PlayGameClick");
                SceneManager.LoadScene("GameScene");
                break;

            case "Restart":
                Debug.Log("PlayGameClick");
                SceneManager.LoadScene("GameScene");
                break;

            case "Quit":
                Debug.Log("Quit");
                Application.Quit();
                break;

        }
    }
}
