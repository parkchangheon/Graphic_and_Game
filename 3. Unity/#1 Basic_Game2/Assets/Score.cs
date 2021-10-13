using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI; //넣어준당

public class Score : MonoBehaviour
{
    public static int score=0; //static 은 클래스에서 관리하는 변수 //클래스 밖에서도 접근해서 편집이 가능
    public static int best_score = 0;
    // Start is called before the first frame update
    void Start()
    {
        score = 0;
        
    }

    // Update is called once per frame
    void Update()
    {
        //텍스트 요소를 가져온다
        GetComponent<Text>().text = score.ToString();
        if (Score.score > Score.best_score)
            Score.best_score = Score.score;
    }

    //Unity boxColider에서 => collision 기본은 물리적이고, Trigger는 투과가 가능하다
}
