using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraShake : MonoBehaviour
{
    public static CameraShake cs;
    public float shakeAmount;
    float shakeTime;
    Vector3 initialPos;

    private void Awake()
    {
        cs = this;
    }

    private void Start()
    { 
        initialPos = this.transform.localPosition;
    }

    public void Shake(float time)
    {
        if (shakeTime > 0)
            return;

        shakeTime = time;
    }


    // Update is called once per frame
    void Update()
    {
        if(shakeTime > 0)
        {
            transform.localPosition = Random.insideUnitSphere * shakeAmount + initialPos;
            shakeTime -= Time.deltaTime;
        }
        else
        {
            shakeTime = 0.0f;
            transform.localPosition = initialPos;
        }
    }
}
