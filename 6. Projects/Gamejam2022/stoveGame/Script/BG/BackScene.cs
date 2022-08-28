using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class BackScene : MonoBehaviour
{
    public void BackSceneBtn()
    {
        SceneManager.LoadScene("MainScene");
    }

}
