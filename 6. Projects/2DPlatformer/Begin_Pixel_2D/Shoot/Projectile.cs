
using UnityEngine;

public class Projectile : MonoBehaviour
{
    [SerializeField] private float speed;
    private float direction;
    private bool Hit;
    private float lifetime;

    private BoxCollider2D boxcollider;
    private Animator anim;

    private void Awake()
    {
        boxcollider = GetComponent<BoxCollider2D>();
        anim = GetComponent<Animator>();
    }

    private void Update()
    {
        if (Hit) return;
        float movementSpeed = speed * Time.deltaTime * direction;
        // 상대좌표를 기준으로 위치시킨다. 절대 좌표로 하고 싶을땐 .position을 사용함
        transform.Translate(movementSpeed, 0, 0);

        lifetime += Time.deltaTime;
        if (lifetime > 3) gameObject.SetActive(false);
    }

    private void OnTriggerEnter2D(Collider2D collision) // 오브젝트간 충돌이 일어날때 처음 한번만 호출
    {
        Hit = true; 
        boxcollider.enabled = false;
        anim.SetTrigger("explode");

        if (collision.tag == "Enemy")
        {
            if(collision.GetComponent<Health>())
                collision.GetComponent<Health>().TakeDamage(1);
            else
                gameObject.SetActive(false);
        }
            
    }

    public void SetDirection(float _direction)
    {
        lifetime = 0;
        direction = _direction;
        gameObject.SetActive(true);
        Hit = false;
        boxcollider.enabled = true;

        float localScaleX = transform.localScale.x;
        if (Mathf.Sign(localScaleX) != _direction)
            localScaleX = -localScaleX;

        transform.localScale = new Vector3(localScaleX, transform.localScale.y, transform.localScale.z); //발사체가 돌아간 방면으로 보내기 위한...
    }

    private void Deactivate()
    {
        Debug.Log("Deactivate has activate!!!");
        gameObject.SetActive(false);
    }
}
