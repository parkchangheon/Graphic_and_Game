using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    /*float currentTime=0f;
    float startingTime=300f;

    [SerializeField] Text CountDownText;

    void Start()
    {
        currentTime = startingTime;
    }
    void Update()
    {
        currentTime -= 1 * Time.deltaTime;
        Debug.Log(currentTime);
        CountDownText.text = currentTime.ToString("0");

        
        if(currentTime <= 0)
        {
            currentTime = 0;
        }
    }*/

    public Text timer;
    public float time;
    float msec;
    float sec;
    float min;

    private void Start()
    {
    
    }

    private void Update()
    {
        time += Time.deltaTime;
    }

    public string GetTiemStr()
    {
        //msec = ((int)(time - (int)time) * 100);
        sec = (int)(time % 60);
        min = (int)(time / 60 % 60);

        return string.Format("{0:00}:{1:00}", min, sec);

    }

}
