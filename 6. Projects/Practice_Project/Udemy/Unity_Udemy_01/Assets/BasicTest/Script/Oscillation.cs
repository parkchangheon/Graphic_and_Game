using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Oscillation : MonoBehaviour
{

    Vector3 startingPosition;
    [SerializeField] Vector3 movementVector;
    [SerializeField] [Range(0,1)]float movementFactor;
    [SerializeField] float period = 2f;
    void Start()
    {
        startingPosition = transform.position;
        Debug.Log(startingPosition);
    }

    void Update()
    {
        if (period <=Mathf.Epsilon) // 매우 작은 수일때.
            return;

        float cycles = Time.time / period;  //시간이 늘어남에 따라 계속 증가 / period
        
        const float tau = Mathf.PI * 2;     // 2ㅠ
        float rawSinWave = Mathf.Sin(cycles * tau); //sin 파

        movementFactor = (rawSinWave + 1f) / 2f;   //-1 ~ 1이던걸 0 ~ 2로 바꾸고 0~1로 다시금 정규화 시킴

        Vector3 offset = movementVector * movementFactor;
        transform.position = startingPosition + offset;
    }
}
