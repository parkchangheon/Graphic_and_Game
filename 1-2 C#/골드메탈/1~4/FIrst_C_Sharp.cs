using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FIrst_C_Sharp : MonoBehaviour  // 모노 비헤이비어는 상속...
{
    // Start is called before the first frame update
    void Start()
    {

        // 주석을 달아준다.
        Debug.Log("Warning Chang is Back");

        int level=5;
        float strength=15.5f;
        string playerName="Sean";
        bool isFullLevel=false;


        /*Debug.Log("용사의 이름은");
        Debug.Log(playerName);

        Debug.Log("레벨은 ???");
        Debug.Log(level);

        Debug.Log("용사의 힘은?");
        Debug.Log(strength);

        Debug.Log("만렙인가??");
        Debug.Log(isFullLevel);

        //2. 그룹형 변수 
        string[] arr = { "슬라임", "사막뱀", "악마" };
        int[] monsterLevel = new int[3];
        monsterLevel[0] = 1;
        monsterLevel[1] = 3;
        monsterLevel[2] = 10;

        for (int i = 0; i < 3; i++)
        {
            Debug.Log(arr[i] + monsterLevel[i]);

        }


        //3. 리스트.

        List<string> items = new List<string>();
        items.Add("생명물약 30"); //먼저
        items.Add("마나 물약 30");
        items.Add("포션 물약 30");

        Debug.Log(items[0]);

        items.RemoveAt(1); // 특정 아이템을 삭제한다. 
        for (int i = 0; i < items.Count; i++) // .Count 리스트 크기 구해준다.
        {
            Debug.Log(items[i]);
        }


        //3. 연산자
        int exp = 1500;

        exp += 20;
        level = exp / 100;
        strength = level * 3.1f;

        Debug.Log(exp);
        Debug.Log(level);
        Debug.Log(strength);


        //4. 비교 연산자 
        bool flag;
        int health = 100;
        int mana = 5;

        flag = health <= 50 && mana <= 20;
        Debug.Log(flag);
        


        //5. 조건문
        if (level == 1)
        {
            Debug.Log("레벨은 1이지만 안나온다");
        }
        else
        {
            Debug.Log("히히 속았지???");
        }

        switch (level)
        {
            case 1:
                Debug.Log("1이다");
                break;
            case 2:
                Debug.Log("2이다");
                break;
            case 3:
                Debug.Log("3이다");
                break;
            case 4:
                Debug.Log("4이다");
                break;
            case 5:
                Debug.Log("5이다");
                break;
            default:
                Debug.Log("5가 넘었다.");
                break;
        }

        




        //6. 반복문

        while (level<=5)
        {
            Debug.Log(level);
            level+=1;
        }

        for(int i = 0; i < 10; i++)
        {
            level++;
        }
        Debug.Log(level);

        //그룹 형 변수 길이!!!!!!!!!!!!!!========================
        // 배열일 경우, .Length 이고, 리스트 일 경우 .Count를 사용해준다.
        string[] arr = { "슬라임", "사막뱀", "악마" };
        foreach(string monster in arr)
        {
            Debug.Log("몬스터는 "+monster);
        }
        
        int health = 100;
        health=Heal(health);
        int[] monsterLevel = new int[3];
        monsterLevel[0] = 1;
        monsterLevel[1] = 3;
        monsterLevel[2] = 10;

        for (int i = 0; i < monsterLevel.Length; i++)
        {
            result(level, monsterLevel[i]);
        }
        */


        //8. 클래스 사용하기
        // 프로젝트 파일에 c# 스크립트 만들고, 거기다가 클래스 만든뒤,
        Actor player = new Actor(); // 인스턴스화
        Debug.Log(player.move());



    }

    //7. 함수(메소드)
    int Heal(int current_health)
    {
        current_health += 10;
        Debug.Log("힐을 받았습니다." + current_health);
        return current_health;
    }

    void result(int hero, int monster)
    {
        if (hero > monster)
            Debug.Log("영웅이 이겼습니다.");
        else
            Debug.Log("괴물이 이겼습니다.");
    }


    // Update is called once per frame
    void Update()
    {
        
    }
}
