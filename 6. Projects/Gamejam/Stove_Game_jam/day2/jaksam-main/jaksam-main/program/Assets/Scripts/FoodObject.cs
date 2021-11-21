using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum CONDITION_TYPE
{
    NONE,
    DISTANCE,
    TIME,
}

public enum MOVE_TYPE
{
    NONE,
    DIRECTIONAL,
    FOLLOW,
    RANDOM,
}

public enum ACTIVATE_TYPE
{
    NONE,
    SPIN,
    CIRCLE,
    LASER,
    BOMB,
    SHOTGUN,
}


public enum FOOD_TYPE
{
    JUNK,
    HEALTH,
}



public class FoodObject : MonoBehaviour
{
    public GameObject target;
    public int idx = -1;

    public FOOD_TYPE foodType = FOOD_TYPE.JUNK;
    public float healthGauge = 0f;

    SpriteRenderer spriteRenderer;

    [Header("Condition")]
    public CONDITION_TYPE conditionType;
    public float conditionValue = 0.0f;
    
    [Header("Move")]
    public MOVE_TYPE moveType;

    public Sprite moveSprite = null;
    public float moveSpeed = 5f;

    public float removeDistance = 5f;

    public bool setMoveCollider = true;
    CircleCollider2D circleCollider;

    float moveTime = 0f;
    public float playTime = 0f;


    [Header("Activate")]
    public ACTIVATE_TYPE activateType;

    public Sprite activateSprite = null;

    public int count = 1;
    public float createTerm = 0.5f;

    public int phaseCount = 1;
    public float phaseTerm = 1f;

    public float subDeleteTiem = 0.0f;
    
    public bool setActivityCollider = true;

    public GameObject[] partObjects;

    void OnEnable()
    {
        // TestCode
        target = GameObject.FindGameObjectWithTag("Player");

        TryGetComponent<SpriteRenderer>(out spriteRenderer);
        TryGetComponent<CircleCollider2D>(out circleCollider);
        

        StartCoroutine(nameof(Condition));
    }

    // Condition
    protected virtual IEnumerator Condition()
    {
        //Debug.Log("Condition");
        bool isPlay = true;

        if (target == null)
        {
            Debug.Log("Condition Error 타겟을 찾을수 없습니다.");
            isPlay = false;
        }

        while (isPlay)
        {
            switch (conditionType)
            {
                case CONDITION_TYPE.DISTANCE:
                    {

                        if ((target.transform.position - this.transform.position).sqrMagnitude < conditionValue * conditionValue)
                        {
                            isPlay = false;
                            break;
                        }
                    }
                    break;

                case CONDITION_TYPE.TIME:
                    {
                        conditionValue -= Time.deltaTime;

                        if (conditionValue <= 0)
                        {
                            Destroy(this.gameObject, 0.5f);
                            isPlay = false;
                            break;
                        }

                    }
                    break;

                default:
                    isPlay = false;
                    break;
            }

            yield return new WaitForEndOfFrame();
        }

        _ = StartCoroutine(nameof(Move));
        yield return null;
    }

    // Move
    protected virtual IEnumerator Move()
    {
        //Debug.Log("Move");

        if (moveSprite != null)
            spriteRenderer.sprite = moveSprite;

        circleCollider.enabled = setMoveCollider;

        bool isPlay = true;
        Vector3 dir = target.transform.position - this.transform.position;
        dir.Normalize();

        if (target == null)
        {
            Debug.Log("Condition Error 타겟을 찾을수 없습니다.");
            isPlay = false;
        }
        Vector3 p = Vector3.zero;

        while (isPlay)
        {
            switch (moveType)
            {
                case MOVE_TYPE.DIRECTIONAL:
                    {
                        this.transform.position += dir * moveSpeed * Time.deltaTime;


                        // 완료 체크
                        Vector3 tdir = (target.transform.position - this.transform.position);
                        if (tdir.sqrMagnitude > removeDistance * removeDistance)
                        {
                            Debug.Log("거리가 멀어져 삭제");

                            Destroy(this.gameObject, 1f);
                            isPlay = false;
                            break;
                        }

                    }
                    break;


                case MOVE_TYPE.FOLLOW:
                    {
                        //transform.position = Vector3.LerpUnclamped(transform.position, target.transform.position, Time.deltaTime);

                        // 일정 거리 안에 들어오면 멈춘다
                        dir = target.transform.position - this.transform.position;
                        float distance = dir.sqrMagnitude;
 
                        this.transform.position += dir.normalized * moveSpeed * Time.deltaTime;

                        if (distance < removeDistance * removeDistance)
                        {
                            isPlay = false;
                            break;
                        }
                    }
                    break;

                case MOVE_TYPE.RANDOM:
                    {

                        


                        if (moveTime <= 0)
                        {
                            p = Random.onUnitSphere;
                            p.z = 0f;
                            moveTime = Random.Range(1f, 4f);

                        }
                        
                        this.transform.position += p.normalized * moveSpeed * Time.deltaTime;
                        moveTime -= Time.deltaTime;
                        playTime -= Time.deltaTime;

                        if (playTime <= 0f )
                        {
                            Destroy(this.gameObject, 1f);
                            isPlay = false;
                            break;
                        }

                        Vector3 tdir = (target.transform.position - this.transform.position);
                        if (tdir.sqrMagnitude > removeDistance * removeDistance)
                        {
                            Debug.Log("거리가 멀어져 삭제");

                            Destroy(this.gameObject, 1f);
                            isPlay = false;
                            break;
                        }
                    }
                    break;


                default:
                    isPlay = false;
                    break;
            }

            yield return new WaitForEndOfFrame();
        }


        _ = StartCoroutine(nameof(Activate));
        yield return null;
    }

    // Activate
    protected virtual IEnumerator Activate()
    {
        //Debug.Log("Activate");

        if (activateSprite != null)
            spriteRenderer.sprite = activateSprite;

        circleCollider.enabled = setActivityCollider;

        for (int j = 0; j < phaseCount; j++)
        {

            switch (activateType)
            {
                case ACTIVATE_TYPE.CIRCLE:
                    {
                        int angle = 360 / count;
                        for (int i = 0; i < 360; i += angle)
                        {
                            GameObject go = Instantiate(partObjects[Random.Range(0,partObjects.Length)]);
                            go.GetComponent<SubFoodObject>().Set(this);

                            if (subDeleteTiem > 0.0f)
                                Destroy(go, subDeleteTiem);

                            go.transform.position = this.transform.position;
                            go.transform.rotation = Quaternion.Euler(0, 0, i);
                        }
                    }
                    break;

                case ACTIVATE_TYPE.LASER:
                    {
                        var rot = target.transform.position - this.transform.position;
                        var angle = Mathf.Atan2(rot.y, rot.x) * Mathf.Rad2Deg;

                        this.transform.rotation = Quaternion.Euler(0, 0, angle - 90);

                        for (int i = 0; i < count; i++)
                        {
                            GameObject go = Instantiate(partObjects[Random.Range(0, partObjects.Length)]);
                            go.GetComponent<SubFoodObject>().Set(this);

                            if (subDeleteTiem > 0.0f)
                                Destroy(go, subDeleteTiem);

                            go.transform.position = this.transform.position;
                            go.transform.rotation = Quaternion.Euler(0, 0, angle);

                            yield return new WaitForSeconds(createTerm);
                        }
                    }
                    break;

                case ACTIVATE_TYPE.SPIN:
                    {
                        int angle = 360 / count;
                        for (int i = 0; i < 360; i += angle)
                        {
                            GameObject go = Instantiate(partObjects[Random.Range(0, partObjects.Length)]);
                            go.GetComponent<SubFoodObject>().Set(this);

                            if (subDeleteTiem > 0.0f)
                                Destroy(go, subDeleteTiem);

                            go.transform.position = this.transform.position;
                            go.transform.rotation = Quaternion.Euler(0, 0, i + (angle * j));

                            yield return new WaitForSeconds(createTerm);
                        }
                    }
                    break;


                case ACTIVATE_TYPE.SHOTGUN:
                    {
                        var rot = target.transform.position - this.transform.position;
                        var targetAngle = Mathf.Atan2(rot.y, rot.x) * Mathf.Rad2Deg;

                        this.transform.rotation = Quaternion.Euler(0, 0, targetAngle);

                        int angle = ((partObjects.Length - 1) * 30) / -2;
                        for (int i = 0; i < partObjects.Length; i ++)
                        {
                            GameObject go = Instantiate(partObjects[i]);
                            go.GetComponent<SubFoodObject>().Set(this);

                            if (subDeleteTiem > 0.0f)
                                Destroy(go, subDeleteTiem);

                            go.transform.position = this.transform.position;
                            go.transform.rotation = Quaternion.Euler(0, 0, targetAngle + angle + i * 30);

                            yield return new WaitForSeconds(createTerm);
                        }
                    }
                    break;

                case ACTIVATE_TYPE.BOMB:
                    {
                        yield return new WaitForSeconds(0.5f);

                        this.transform.localScale = Vector3.one * Random.Range(1f, 1.5f);
                        GameObject go = Instantiate(partObjects[0]);
                        go.GetComponent<SubFoodObject>().Set(this);

                        if (subDeleteTiem > 0.0f)
                            Destroy(go, subDeleteTiem);

                        spriteRenderer.enabled=false;

                        go.transform.position = this.transform.position;
                        go.transform.rotation = Quaternion.Euler(0, 0, Random.Range(0, 259));
                        go.transform.localScale = Vector3.one * Random.Range(3f, 5f);
                    }
                    break;


            }

            yield return new WaitForSeconds(phaseTerm);
        }


        Destroy(this.gameObject, 1f);
        yield return null;
    }

    private void OnDestroy()
    {
        GameManager.gm.FoodOff(this);
    }



    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            GameManager.gm.SetGuage(healthGauge);

            if (foodType == FOOD_TYPE.JUNK)
            {
                CameraShake.cs.Shake(0.5f);
            }

            Destroy(this.gameObject);
        }
    }
}
