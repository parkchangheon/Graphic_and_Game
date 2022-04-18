using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Hello Unity");


        // 1. 변수선언
        int level = 5;
        float strength = 15.5f;
        string playername ="나검사";
        bool isFullLevel = false;

        Debug.Log("용사의 이름음?");
        Debug.Log(playername);
        Debug.Log("용사의 레벨은??");
        Debug.Log(level);


        // 2. 그룹형 변수
        // 배열
        string[] monster = { "슬라임", "사막뱀", "악마" };
        for(int i = 0; i < 3; i++)
        {
            Debug.Log(monster[i]);
        }


        int[] monsterlevel = new int[3];  // 동적할당
        monsterlevel[0] = 1;
        monsterlevel[1] = 2;
        monsterlevel[2] = 3;

        Debug.Log("맵에 존재하는 몬스터의 레벨");
        for (int i = 0; i < 3; i++)
        {
            Debug.Log(monsterlevel[i]);
        }


        // 리스트
        List<string> items = new List<string>(); //제네릭?
        items.Add("마나 물약");
        items.Add("생명의 물약");

        items.RemoveAt(0); //해당 위치 아이템 삭제

        Debug.Log(items[0]);



        // 3. 연산자
        int exp = 1500;
        exp = 1500 + 320;
        exp -= 10;
        level = exp / 300;
        strength = level * 3.1f;


        int nextExp = 300 - (exp % 300);
        Debug.Log("다음 레벨까지 남은 경험치는? ");
        Debug.Log(nextExp);

        int fullLevel = 30;
        isFullLevel = level == fullLevel;
        Debug.Log("용사는 만렙입니까? " + isFullLevel);
        bool isEndTutorial = level > 10;
        Debug.Log("튜토리얼이 끝난 용사입니까? " + isEndTutorial);

        int health = 30;
        int mana = 25;
        bool isBadCondition = health <= 50 && mana <= 20;
        Debug.Log("용사의 상태가 나쁩니까? " + isBadCondition);

        string condition = isBadCondition ? "나쁨" : "좋음";
        Debug.Log("용사의 상태가 나쁩니까?" + condition);



        // 4. 키워드


        // 5. 조건문 
        if (condition == "나쁨")
            Debug.Log("용사의 상태가 나쁘다.");
        else
            Debug.Log("상태는 나쁘지는 않았다.");

        if (isBadCondition && items[0] == "생명의 물약")
        {
            health += 20;
            Debug.Log("생명의 물약을 사용했습니다.");
        }
        else if (isBadCondition && items[0] == "마나 물약")
        {
            mana += 20;
            Debug.Log("마나의 물약을 사용했습니다.");
        }


        switch(monster[0])
        {
            case "슬라임":
            case "패럿":
                Debug.Log("슬라임이다!!");
                break;

            case "사막뱀":
                Debug.Log("사막뱀이다!!!");
                break;

            case "악마":
                Debug.Log("악마출현이다!!!");
                break;

            default:
                Debug.Log("알 수 없는 몬스터 출현!!");
                break;
        }



        // 6. 반복문
        while (health>0)
        {
            health--;
            if (health > 0)
                Debug.Log("독 데미지를 입었습니다." + health);
            else
                Debug.Log("사망하였습니다.");

            if (health == 10)
            {
                Debug.Log("해독제를 사용했다.");
                break;
            }
        }

        for(int count = 0; count < 10; count++)
        {
            health++;
            Debug.Log("붕대로 치료중..." + health);
        }

        for(int count=0;count<monster.Length;count++)
        {
            Debug.Log("이 지역에 있는 몬스터 : " + monster[count]);
        }

        foreach (string m in monster)
        {
            Debug.Log("몬스터들의 이름은 " + m);
        }



        // 7. 함수 (메소드)
        health = Heal(health);

        for(int i=0;i<monster.Length;i++)
        {
            Debug.Log(Battle(monsterlevel[i], level));
        }




        // 8. 클래스 
        Actor player = new Actor();  //인스턴스화 (클래스를 변수화 시키는 것)
        player.name = "박아처";
        player.level = 50;
        Debug.Log(player.name + "의 레벨은 " + player.level + " 입니다.");

    }

    // Update is called once per frame
    void Update()
    {
        
    }


    //힐을 받는 함수
    int Heal(int Chealth)
    {
        Chealth += 10;
        Debug.Log("힐을 받았습니다. " + Chealth);
        return Chealth;
    }

    string Battle(int mon, int lev)
    {
        if (mon > lev)
            return "졌다";

        else
            return "이겼다.";
    }


}
