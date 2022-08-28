using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    [SerializeField] float setTime = 60.0f;
    [SerializeField] Text countdownText;

    private void Awake()
    {
        Start();
    }

    private void Start()
    {
        countdownText.text = setTime.ToString();
    }


    private void Update()
    {
        if (setTime > 0)
            setTime -= Time.deltaTime;
        else if (setTime <= 0)
        {
            SceneManager.LoadScene("GameOverScene");

        }
        countdownText.text = Mathf.Round(setTime).ToString();

    }
}
