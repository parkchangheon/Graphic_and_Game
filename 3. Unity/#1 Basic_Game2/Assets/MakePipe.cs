using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MakePipe : MonoBehaviour
{

    public GameObject pipe;    //prefab이된 파이프 오브젝트를 끌어 넣을 수 있다.(아까 만든)
    public float timeDiff;
    float Timer=0;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Timer += Time.deltaTime;
        if(Timer>timeDiff)
        {
            GameObject newpipe = Instantiate(pipe); //위에서 만든 파이프 객체를 찍어내거라
            newpipe.transform.position = new Vector3(3, Random.Range(-3.0f,3.1f), 0);
            Timer = 0;
            Destroy(newpipe,6);
        }
    }
}
